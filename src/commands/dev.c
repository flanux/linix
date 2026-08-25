#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <stdio.h>

#include <linix/command.h>

static void list_devices(void)
{
	DIR *dir = opendir("/dev");

	if (dir == NULL) {
		perror("dev: opendir");
		return;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.') {
			continue;
		}

		printf("%s\n", entry->d_name);
	}

	closedir(dir);
}

int linix_cmd_dev(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	list_devices();

	return 0;
}

LINIX_REGISTER_COMMAND("dev", linix_cmd_dev)
