#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>

static void print_ids(void)
{
	printf("uid: %u\n", getuid());
	printf("euid: %u\n", geteuid());
	printf("gid: %u\n", getgid());
	printf("egid: %u\n", getegid());
}

int linix_cmd_id(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	print_ids();

	return 0;
}

LINIX_REGISTER_COMMAND("id", linix_cmd_id)
