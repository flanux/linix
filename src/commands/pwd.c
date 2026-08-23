#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_pwd(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *buffer = getcwd(NULL, 0);

	if (buffer == NULL) {
		linix_perror("pwd");
		return 1;
	}

	printf("%s\n", buffer);
	
	free(buffer);

	return 0;
}
