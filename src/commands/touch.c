#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <linix/command.h>

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
		perror("linix touch");
		return 1;
	}

	close(fd);
	return 0;
}
