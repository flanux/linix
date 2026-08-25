#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <linix/command.h>

int linix_cmd_kill(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "usage: kill PID SIGNAL\n");
		return 1;
	}

	pid_t pid = (pid_t)strtol(argv[1], NULL, 10);
	int sig = (int)strtol(argv[2], NULL, 10);

	if (kill(pid, sig) == -1) {
		perror("kill");
		return 1;
	}

	return 0;
}

LINIX_REGISTER_COMMAND("kill", linix_cmd_kill)
