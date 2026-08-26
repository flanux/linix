#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#include <linix/command.h>

static int print_capabilities(void)
{
	FILE *file = fopen("/proc/self/status", "r");

	if (file == NULL) {
		perror("caps: fopen");
		return -1;
	}

	char line[256];

	while (fgets(
		line, sizeof(line), file
	) != NULL) {
		if (strncmp(line, "Cap", 3) == 0) {
			printf("%s", line);
		}
	}

	fclose(file);

	return 0;
}

int linix_cmd_caps(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	return print_capabilities() == -1 ? 1 : 0;
}

LINIX_REGISTER_COMMAND("caps", linix_cmd_caps)
