/*
 * Countdown timer
 *
 * Copyright (C) 2014-2015  Tomasz Kramkowski <tk@the-tk.com>
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

static const unsigned long long SEC_SECOND = 1, SEC_MINUTE = 60,
	     SEC_HOUR = 3600, SEC_DAY = 86400, SEC_MONTH = 2629746,
	     SEC_YEAR = 31556940;
static const unsigned long interval_nsec = 1000000000 / 4;

volatile unsigned short term_width = 0;

void sigwinch(int sig) {
	struct winsize ws;

	if (sig != SIGWINCH)
		return;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		error(1, errno, "Failed to get terminal width");

	term_width = ws.ws_col;
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

void format_dmy(char *dest, size_t size, const char *name,
		unsigned long long count)
{
	if (count == 1)
		snprintf(dest, size, "%llu %s, ", count, name);
	else if (count > 1)
		snprintf(dest, size, "%llu %ss, ", count, name);
	else
		dest[0] = '\0';
}

void print_time(unsigned long long total_sec, bool show_colon)
{
	unsigned long long count, hours, minutes, seconds;
	char colon = show_colon ? ':' : ' ', syears[128], smonths[16], sdays[16];

	count = total_sec / SEC_YEAR;
	total_sec %= SEC_YEAR;
	format_dmy(syears, sizeof syears, "year", count);

	count = total_sec / SEC_MONTH;
	total_sec %= SEC_MONTH;
	format_dmy(smonths, sizeof smonths, "month", count);

	count = total_sec / SEC_DAY;
	total_sec %= SEC_DAY;
	format_dmy(sdays, sizeof sdays, "day", count);

	hours = total_sec / SEC_HOUR;
	total_sec %= SEC_HOUR;

	minutes = total_sec / SEC_MINUTE;
	total_sec %= SEC_MINUTE;

	seconds = total_sec / SEC_SECOND;
	total_sec %= SEC_SECOND;

	if (total_sec != 0)
		error(1, 0, "A bug occured during time formatting");

	printf(" %s%s%s%.2llu%c%.2llu%c%.2llu\r", syears, smonths, sdays, hours,
	       colon, minutes, colon, seconds);

	if (fflush(stdout) != 0)
		error(1, errno, "Failed to flush stdout");
}

unsigned long long get_seconds(char *code)
{
	size_t length = strlen(code);
	unsigned long long multiplier, retval;
	char suffix, value[length];

	if (length < 2)
		return 0;

	suffix = code[length - 1];
	switch (suffix) {
		case 's': multiplier = SEC_SECOND; break; /* 1 second */
		case 'm': multiplier = SEC_MINUTE; break; /* 1 minute */
		case 'h': multiplier = SEC_HOUR; break;	  /* 1 hour */
		case 'D': multiplier = SEC_DAY; break;	  /* 1 day */
		case 'M': multiplier = SEC_MONTH; break;  /* 30.4368 days */
		case 'Y': multiplier = SEC_YEAR; break;	  /* 365.242 days */
		default: return 0;
	}

	strncpy(value, code, sizeof value);

	value[sizeof value - 1] = '\0';

	errno = 0;
	retval = strtoul(value, NULL, 10) * multiplier; /* Possibly might overflow */
	if (retval == ULONG_MAX && errno != 0)
		error(1, errno, "Error converting time specifier %s", code);

	return retval;
}

int main(int argc, char **argv)
{
	bool blink = false;
	int sig;
	sigset_t sigset;
	struct itimerspec its = {{0, interval_nsec}, {0, interval_nsec}};
	struct sigaction sigact = {.sa_handler = sigwinch};
	timer_t timerid;
	struct sigevent sev = {.sigev_notify = SIGEV_SIGNAL,
		.sigev_signo = SIGRTMIN, .sigev_value.sival_ptr = &timerid};
	unsigned long long total_seconds = 0;

	if (!isatty(STDOUT_FILENO))
		error(1, 0, "Error: stdout is not a tty");

	if (argc < 2)
		error(1, 0, "Not enough arguments.\nUsage:\n"
		      "\t%s <n>{s,m,h,D,M,Y} ...", argv[0]);

	for (int i = 1; i < argc; i++)
		total_seconds += get_seconds(argv[i]);

	if (sigaction(SIGWINCH, &sigact, NULL) != 0)
		error(1, errno, "Unable to set SIGWINCH signal action");

	if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) != 0)
		error(1, errno, "Could not create timer");

	if (sigemptyset(&sigset) != 0)
		error(1, errno, "Could not empty signal set");

	if (sigaddset(&sigset, SIGRTMIN) != 0)
		error(1, errno, "Could not add SIGRTMIN to signal set");

	if (sigprocmask(SIG_BLOCK, &sigset, NULL) != 0)
		error(1, errno, "Could not block SIGRTMIN");

	if (timer_settime(timerid, 0, &its, NULL) != 0)
		error(1, errno, "Could not set timer");

	sigwinch(SIGWINCH);

	for (unsigned long long i = 0; i < total_seconds; i++)
		for (int ii = 0; ii < 4; ii++) {
			if (sigwait(&sigset, &sig), sig != SIGRTMIN)
				error(1, 0, "sigwait returned unexpected signal %d", sig);
			if (sigaddset(&sigset, SIGRTMIN) != 0)
				error(1, errno, "Could not add SIGRTMIN to signal set");

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
			error(1, errno, "Could not add SIGRTMIN to signal set");

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
