#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <linix/command.h>
#include <linix/io.h>

int linix_cmd_cat(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix cat: missing the file operand\n");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1) {
		perror("linix cat");
		return 1;
	}

	char buffer[4096];

	ssize_t n;

	while ((n=read(fd, buffer, sizeof(buffer))) > 0) {

		if (linix_write_all(
			STDOUT_FILENO,
			buffer,
			n
		) == -1 ) {

			perror("linix cat");
			close(fd);
			return 1;
		}
	}

	if (n == -1) {
		perror("linix cat");
		close(fd);
		return 1;
	}

	close(fd);

	return 0;
}
