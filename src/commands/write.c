#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <linix/command.h>

static int write_file(const char *path, const char *text) 
{
	int fd = open(
		path,
		O_WRONLY | O_CREAT | O_TRUNC,
		0644
	);

	if (fd == -1) {
		perror("write: open");
		return -1;
	}
	
	size_t length = strlen(text);

	ssize_t written = write(
		fd,
		text,
		length
	);

	if (written == -1) {
		perror("write");
		close(fd);
		return -1;
	}

	close(fd);

	return written == (ssize_t)length ? 0 : -1;
}

int linix_cmd_write(int argc, char **argv) {
	if (argc != 3) {
		fprintf(
			stderr,
			"usage: write <file> <text> \n"
		);

		return 1;
	}

	if (write_file(argv[1], argv[2]) == -1) {
		return 1;
	}

	return 0;
}

LINIX_REGISTER_COMMAND("write", linix_cmd_write)
