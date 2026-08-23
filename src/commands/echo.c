#include <stdio.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_echo(int argc, char **argv)
{
	for (int i=1; i<argc; i++) {

		printf("%s", argv[i]);

		if (i < argc-1)
			printf(" ");
	}
	printf("\n");

	return 0;
}
