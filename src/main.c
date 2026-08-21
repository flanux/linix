#include <stdio.h>
#include <string.h>

#include <linix/command.h>

static LinixCommand commands[] = {
	{
		.name = "pwd",
		.fn = linix_cmd_pwd
	},
	{
		.name = "cat",
		.fn = linix_cmd_cat
	},
	{
		.name = "echo",
		.fn = linix_cmd_echo
	},
	{
		.name = "touch",
		.fn = linix_cmd_touch
	},
	{
		.name = "mkdir",
		.fn = linix_cmd_mkdir
	},
	{
		.name = "rm",
		.fn = linix_cmd_rm
	},
	{
		.name = "ls",
		.fn = linix_cmd_ls
	},
	{
		.name = "cp",
		.fn = linix_cmd_cp
	}
};

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr,
	  "usage: %s <command> [args...]\n", argv[0]);
		return 1;
	}

	size_t command_count = 
		sizeof(commands) / sizeof(commands[0]);

	for (size_t i=0; i<command_count; i++) {
		if (strcmp(argv[1], commands[i].name) == 0) {
			return commands[i].fn(
				argc-1,
				argv+1
			);
		}
	}

	if (strcmp(argv[1], "help") == 0) {
		printf("linix commands:\n");

		for (size_t i=0; i<command_count; i++)
			printf(" %s\n", commands[i].name);

		return 0;
	}

	fprintf(stderr,
	 "linix: unknown command: %s\n", argv[1]);
	return 1;
}
