#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <linix/command.h>

int linix_cmd_run(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: run COMMAND [ARGS...]\n");
		return 1;
	}

	pid_t pid = fork();

	if (pid == -1) {
		perror("run: fork");
		return 1;
	}

	if (pid == 0) {
		execvp(argv[1], &argv[1]);

		perror("run: exec");
		_exit(127);
	}

	int status;

	if (waitpid(pid, &status, 0) == -1) {
		perror("run: waitpid");
		return 1;
	}

	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	}

	return 1;
}

LINIX_REGISTER_COMMAND("run", linix_cmd_run)
