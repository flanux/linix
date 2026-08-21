#include <stdio.h>

#include <linix/command.h>

int linix_cmd_mv(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr,
	  		"linix mv: missing file operand\n");
		return 1;
	}

	if (rename(argv[1], argv[2]) == -1) {
		perror("linix mv");
		return 1;
	}

	return 0;
}
