#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>

int linix_cmd_tty(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *name = ttyname(STDIN_FILENO);

	if (name == NULL) {
		perror("tty");
		return 1;
	}

	printf("%s\n", name);

	return 0;
}

LINIX_REGISTER_COMMAND("tty", linix_cmd_tty)
