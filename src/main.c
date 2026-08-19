#include <stdio.h>
#include <string.h>

#include <linix/command.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr,
	  "usage: %s <command> [args...]\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "pwd") == 0)
		return linix_cmd_pwd(argc-1, argv+1);

	if (strcmp(argv[1], "help") == 0) {
		printf("linix commands:\n");
		printf(" pwd\n");
		return 0;
	}

	fprintf(stderr,
	 "linix: unknown command: %s\n", argv[1]);
	return 1;
}
