#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

#include <linix/command.h>

int linix_cmd_mounts(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	FILE *file = fopen("/proc/mounts", "r");

	if (file == NULL) {
		perror("mounts: fopen");
		return 1;
	}

	char line[1024];

	while (fgets(
		line,
		sizeof(line),
		file
	) != NULL) {
		printf("%s", line);
	}

	fclose(file);

	return 0;
}

LINIX_REGISTER_COMMAND("mounts", linix_cmd_mounts)
