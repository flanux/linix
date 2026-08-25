#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <linix/command.h>

int linix_cmd_env(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int fd = open("/proc/self/environ", O_RDONLY);

	if (fd == -1) {
		perror("env: open");
		return 1;
	}

	char buffer[4096];
	ssize_t n;

	while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
		for (ssize_t i=0; i<n; i++) {
			if (buffer[i] == '\0') {
				putchar('\n');
			} else {
				putchar(buffer[i]);
			}
		}
	}

	if (n==-1) {
		perror("env: read");
		close(fd);
		return 1;
	}

	close(fd);

	return 0;
}

LINIX_REGISTER_COMMAND("env", linix_cmd_env)
