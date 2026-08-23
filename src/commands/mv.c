#include <stdio.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_mv(int argc, char **argv)
{
	if (argc < 3) {
		fprintf(stderr,
	  		"mv: missing file operand\n");
		return 1;
	}

	if (rename(argv[1], argv[2]) == -1) {
		linix_perror("mv");
		return 1;
	}

	return 0;
}

LINIX_REGISTER_COMMAND("mv", linix_cmd_mv)
