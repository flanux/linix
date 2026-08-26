#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <linix/command.h>

static void child_process(int pipefd[2])
{
	close(pipefd[1]);

	char buffer[128];

	ssize_t n = read(
		pipefd[0],
		buffer,
		sizeof(buffer) -1
	);

	if (n > 0) {
		buffer[n] = '\0';
		printf("child received: %s", buffer);
	}

	close(pipefd[0]);
}

static void parent_process(
	int pipefd[2],
	pid_t pid
)
{
	close(pipefd[0]);

	const char message[] = "hello thorugh pipe\n";

	write(
		pipefd[1],
		message,
		sizeof(message) -1
	);

	close(pipefd[1]);

	waitpid(pid, NULL, 0);

	printf("parent: child finished\n");
}

int linix_cmd_pipe(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int pipefd[2];

	if (pipe(pipefd) == -1 ) {
		perror("pipe");
		return 1;
	}

	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return 1;
	}

	if (pid == 0) {
		child_process(pipefd);
		return 0;
	}

	parent_process(pipefd, pid);

	return 0;
}

LINIX_REGISTER_COMMAND("pipe", linix_cmd_pipe)
