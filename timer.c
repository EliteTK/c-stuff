/*
 * Countdown timer
 *
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

#define SEC_SECOND        1
#define SEC_MINUTE       60
#define SEC_HOUR       3600
#define SEC_DAY       86400
#define SEC_MONTH   2629746
#define SEC_YEAR   31556940

static const unsigned long interval_nsec = 1000000000 / 4;
unsigned short term_width = 0; /* Maybe volatile? */

void sigwinch(int sig) {
	if (sig != SIGWINCH)
		return;

	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		error(1, errno, "Failed to get terminal width");

	term_width = ws.ws_col;
}

unsigned long int get_seconds(char *code)
{
	int length = strlen(code), multiplier = 0;
	char suffix = code[length - 1], value[length + 1];
	unsigned long retval;

	if (length < 2) {
		return 0;
	}

	switch (suffix) {
		case 's': multiplier = SEC_SECOND; break; // 1 second
		case 'm': multiplier = SEC_MINUTE; break; // 1 minute
		case 'h': multiplier = SEC_HOUR;   break; // 1 hour
		case 'D': multiplier = SEC_DAY;    break; // 1 day
		case 'M': multiplier = SEC_MONTH;  break; // 30.4368 days
		case 'Y': multiplier = SEC_YEAR;   break; // 365.242 days
		default : return 0;
	}

	strncpy(value, code, length + 1);

	value[length - 1] = '\0';

	errno = 0;

	retval = strtoul(value, NULL, 10) * multiplier;

	if (retval == ULONG_MAX && errno != 0)
		error(1, errno, "Error converting time specifier %s", code);

	return retval;
}

void clear_line(void)
{
	if (term_width <= 1)
		return;

	for (unsigned short i = 0; i < term_width - 1; i++)
		putchar(' ');

	putchar('\r');

	if (fflush(stdout) != 0)
		error(1, errno, "Failed to flush stdout");
}


void print_time(unsigned long total_sec, bool show_colon)
{
	unsigned long years, months, days, hours, minutes, seconds;
	char colon = show_colon ? ':' : ' ', syears[128], smonths[16],
	     sdays[16];

	years = total_sec / SEC_YEAR;
	total_sec %= SEC_YEAR;

	if (years == 1)
		snprintf(syears, sizeof syears, "%lu year, ", years);
	else if (years > 1)
		snprintf(syears, sizeof syears, "%lu years, ", years);
	else
		syears[0] = '\0';

	months = total_sec / SEC_MONTH;
	total_sec %= SEC_MONTH;

	if (months == 1)
		snprintf(smonths, sizeof smonths, "%lu month, ", months);
	else if (months > 1)
		snprintf(smonths, sizeof smonths, "%lu months, ", months);
	else
		smonths[0] = '\0';

	days = total_sec / SEC_DAY;
	total_sec %= SEC_DAY;

	if (days == 1)
		snprintf(sdays, sizeof sdays, "%lu day, ", days);
	else if (days > 1)
		snprintf(sdays, sizeof sdays, "%lu days, ", days);
	else
		sdays[0] = '\0';

	hours = total_sec / SEC_HOUR;
	total_sec %= SEC_HOUR;

	minutes = total_sec / SEC_MINUTE;
	total_sec %= SEC_MINUTE;

	seconds = total_sec / SEC_SECOND;
	total_sec %= SEC_SECOND;

	if (total_sec != 0)
		error(1, 0, "An error occured during time formatting");

	printf(" %s%s%s%.2lu%c%.2lu%c%.2lu\r", syears, smonths, sdays, hours,
	       colon, minutes, colon, seconds);

	if (fflush(stdout) != 0)
		error(1, errno, "Failed to flush stdout");
}

void usage(char *cmd)
{
	printf("Usage:\n\t%s <n>{s,m,h,D,M,Y} ...\n", cmd);
}

int main(int argc, char **argv)
{
	bool blink = false;
	int sig;
	sigset_t sigset;
	struct itimerspec its;
	struct sigevent sev;
	struct sigaction sigact;
	timer_t timerid;

	unsigned long total_seconds = 0;

	if (argc < 2) {
		printf("Not enough arguments.\n");
		usage(argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; i++)
		total_seconds += get_seconds(argv[i]);

	sigact.sa_handler = sigwinch;

	if (sigaction(SIGWINCH, &sigact, NULL) != 0)
		error(1, errno, "Unable to set SIGWINCH signal action");

	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = &timerid;

	if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) != 0)
		error(1, errno, "Could not create timer");

	its = (struct itimerspec){
		{0, interval_nsec},
		{0, interval_nsec}
	};

	if (sigemptyset(&sigset) != 0)
		error(1, errno, "Could not empty signal set");

	if (sigaddset(&sigset, SIGRTMIN) != 0)
		error(1, errno, "Could not add SIGRTMIN to signal set");

	if (sigprocmask(SIG_BLOCK, &sigset, NULL) != 0)
		error(1, errno, "Could not block SIGRTMIN");

	if (timer_settime(timerid, 0, &its, NULL) != 0)
		error(1, errno, "Could not set timer");

	sigwinch(SIGWINCH);

	for (unsigned long i = 0; i < total_seconds; i++)
		for (int ii = 0; ii < 4; ii++) {
			if (sigwait(&sigset, &sig), sig != SIGRTMIN)
				error(1, 0, "sigwait returned unexpected signal %d", sig);
			if (sigaddset(&sigset, SIGRTMIN) != 0)
				error(1, errno, "Could not add signal to set");

			clear_line();
			print_time(total_seconds - i, ii < 2);
		}

	if (sigaddset(&sigset, SIGINT) != 0)
		error(1, errno, "Could not add SIGINT to signal set");

	while (true) {
		blink = !blink;
		sigwait(&sigset, &sig);
		if (sig != SIGRTMIN)
			break;

		if (sigaddset(&sigset, SIGRTMIN) != 0)
			error(1, errno, "Could not add signal to set");

		clear_line();

		if (blink)
			printf(" -- BEEP -- \a\r");

		if (fflush(stdout) != 0)
			error(1, errno, "Failed to flush stdout");
	}

	timer_delete(timerid);

	clear_line();

	return 0;
}
