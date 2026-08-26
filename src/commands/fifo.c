#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linix/command.h>

static int create_fifo(const char *path)
{
	if (mkfifo(path, 0600) == -1) {
		perror("fifo: mkfifo");
		return -1;
	}

	printf("created FIFO: %s\n", path);

	return 0;
}

int linix_cmd_fifo(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	const char *path = "/tmp/linix.fifo";

	if (create_fifo(path) == -1) {
		return 1;
	}

	printf("write with: echo hello > %s\n", path);
	printf("remove with: rm %s\n", path);

	return 0;
}

LINIX_REGISTER_COMMAND("fifo", linix_cmd_fifo)
