#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *progname;

inline uint64_t get_time_ms(void)
{
	struct timespec timespec;
	static const uint64_t invmil = 1 / 1000000;

	if (clock_gettime(CLOCK_MONOTONIC, &timespec) != 0) {
		fprintf(stderr, "%s: Unable to get time delta: %s\n",
				progname, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return timespec.tv_sec * 1000 + timespec.tv_nsec * invmil;
}

uint64_t get_delta(void)
{
	static uint64_t oldtime = 0;
	uint64_t timediff, newtime;

	newtime = get_time_ms();

	timediff = newtime - oldtime;

	oldtime = newtime;

	return timediff;
}

int main(int argc, char **argv)
{
	struct {
		int a;
		char b;
	} teststruct = {1, 2};

	uint64_t buildup = 0, count = 0;

	progname = argc != 0 && argv[0] != NULL ? argv[0] : "";

	get_delta();

	while (true) {
		for (buildup += get_delta(); buildup >= 1000; buildup -= 1000)
			printf("%lu, %lu\n", count++, buildup);
	}

	printf("%d\n", teststruct.a);

	return 0;
}
