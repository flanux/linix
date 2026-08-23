#include <stdio.h>
#include <sys/stat.h>

#include <linix/command.h>

int linix_cmd_mkdir(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix mkdir: missing operand\n");
		return 1;
	}

	for (int i=1; i<argc; i++) {
		if (mkdir(argv[i], 0755) == -1) {
			perror("linix mkdir");
			return 1;
		}
	}

	return 0;
}
