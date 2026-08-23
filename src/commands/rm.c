#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_rm(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "linix rm mising operand ");
		return 1;
	}
	
	for (int i=1; i<argc; i++) {
		if (unlink(argv[i]) == -1) {
			linix_perror("rm");
			return 1;
		}
	}

	return 0;
}

LINIX_REGISTER_COMMAND("rm", linix_cmd_rm)
