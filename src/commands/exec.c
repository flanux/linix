#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>

static int execute_program(
	char *program,
	char **args
)
{
	execvp(program, args);
	
	perror("exec");
	return 1;
}

int linix_cmd_exec(
	int argc,
	char **argv
) {

	if (argc < 2) {
		fprintf(
			stderr,
			"usage: exec <program> [args...]\n"
		);

		return 1;
	}

	if (execute_program(
		argv[1],
		&argv[1]
	) == -1) {
		return 1;
	}

	return 0;
}

LINIX_REGISTER_COMMAND("exec", linix_cmd_exec)
