#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <linix/command.h>
#include <linix/io.h>
#include <linix/error.h>

int linix_cmd_cat(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix cat: missing the file operand\n");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1) {
		linix_perror("cat");
		return 1;
	}

	char buffer[4096];

	ssize_t n;

	for (;;) {
		n = read(fd, buffer, sizeof(buffer));

		if (n == -1 && errno == EINTR)
			continue;

		if (n <= 0)
			break;

		if (linix_write_all(
			STDOUT_FILENO,
			buffer,
			n
		) == -1) {
			linix_perror("cat");
			close(fd);
			return 1;
		}
	}

	if (n == -1) {
		linix_perror("cat");
		close(fd);
		return 1;
	}

	close(fd);

	return 0;
}
