#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <linix/command.h>
#include <linix/io.h>

int linix_cmd_cp(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr,
	  		"linix cp: missing file operand\n");
		return 1;
	}

	int source_fd = open(argv[1], O_RDONLY);

	if (source_fd == -1) {
		perror("linix cp");
		return 1;
	}

	int destination_fd = open(
		argv[2],
		O_WRONLY | O_CREAT | O_TRUNC,
		0644
	);

	if (destination_fd == -1) {
		perror("linix cp");
		close(source_fd);
		return 1;
	}

	char buffer[4096];
	ssize_t n;

	while ((n = read(source_fd, buffer, sizeof(buffer))) > 0) {

		if (linix_write_all(
			destination_fd,
			buffer,
			n
		) == -1) {
			perror("linix cp");

			close(source_fd);
			close(destination_fd);

			return 1;
		}
	}

	if (n == -1) {
		perror("linix cp");

		close(source_fd);
		close(destination_fd);

		return 1;
	}

	close(source_fd);
	close(destination_fd);

	return 0;
}
