#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>

#include <linix/command.h>

static int print_clock(
	clockid_t clock,
	const char *name
) {

	struct timespec ts;

	if (clock_gettime(clock, &ts) == -1) {
		perror(name);
		return -1;
	}

	printf(
		"%-10s %lld.%09ld\n",
		name,
		(long long)ts.tv_sec,
		ts.tv_nsec
	);

	return 0;
}

int linix_cmd_time(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	print_clock(
		CLOCK_REALTIME,
		"realtime"
	);

	print_clock(
		CLOCK_MONOTONIC,
		"monotonic"
	);

	return 0;
}

LINIX_REGISTER_COMMAND("time", linix_cmd_time)
