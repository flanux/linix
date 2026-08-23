#define _POSIX_C_SOURCE 2000809L

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_touch(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix touch: missing file opearand");
		return 1;
	}

	int fd = open(
		argv[1],
		O_CREAT | O_WRONLY,
		0644
	);

	if (fd == -1) {
		linix_perror("touch");
		return 1;
	}

	close(fd);

	if (utimensat(AT_FDCWD, argv[1], NULL, 0) == -1) {
		linix_perror("touch");
		return 1;
	}

	return 0;
}

LINIX_REGISTER_COMMAND("touch", linix_cmd_touch)
