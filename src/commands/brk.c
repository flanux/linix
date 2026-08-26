#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>

#include <linix/command.h>

static void *current_break(void)
{
	return sbrk(0);
}

int linix_cmd_brk(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	void *before = current_break();

	if (before == (void *)-1) {
		perror("brk: sbrk");
		return 1;
	}

	printf("program break: %p\n", before);

	return 0;
}

LINIX_REGISTER_COMMAND("brk", linix_cmd_brk)
