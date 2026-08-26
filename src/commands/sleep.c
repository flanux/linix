#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <linix/command.h>

static int sleep_seconds(unsigned int seconds)
{
	struct timespec request = {
		.tv_sec = seconds,
		.tv_nsec = 0
	};

	return nanosleep(&request, NULL);
}

int linix_cmd_sleep(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: sleep <sconds>\n");
		return 1;
	}

	unsigned int seconds = strtoul(argv[1], NULL, 10);

	printf("sleeping or %u seconds...\n", seconds);

	if (sleep_seconds(seconds) == -1) {
		perror("sleep");
		return 1;
	}

	printf("done\n");

	return 0;
}

LINIX_REGISTER_COMMAND("sleep", linix_cmd_sleep)
