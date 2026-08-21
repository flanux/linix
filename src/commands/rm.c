#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>

int linix_cmd_rm(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix rm mising operand ");
		return 1;
	}

	if (unlink(argv[1]) == -1) {
		perror("linix rm");
		return 1;
	}

	return 0;
}
