#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#include <linix/command.h>

static void print_meminfo(const char *name)
{
	FILE *file = fopen("/proc/meminfo", "r");

	if (file == NULL) {
		perror("mem: fopen");
		return;
	}

	char line[256];

	while (fgets(
		line,
		sizeof(line),
		file
	) != NULL) {
		if (strncmp(
			line,
			name,
			strlen(name)
		) == 0) {
			printf("%s", line);
			break;
		}
	}

	fclose(file);
}

int linix_cmd_mem(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	print_meminfo("MemTotal:");
	print_meminfo("MemAvailable:");
	print_meminfo("SwapTotal:");
	print_meminfo("SwapFree:");

	return 0;
}

LINIX_REGISTER_COMMAND("mem", linix_cmd_mem)
