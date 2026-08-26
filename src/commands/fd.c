#define _POISX_C_SOURCE 200809L

#include <dirent.h>
#include <stdio.h>

#include <linix/command.h>

static void list_fds(void)
{
	DIR *dir = opendir("/proc/self/fd");

	if (dir == NULL) {
		perror("fd: opendir");
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

int linix_cmd_fd(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	list_fds();

	return 0;
}

LINIX_REGISTER_COMMAND("fd", linix_cmd_fd)
