#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <stdio.h>

#include <linix/command.h>

static void list_class(const char *name)
{
	char path[256];

	snprintf(
		path,
		sizeof(path),
		"/sys/class/%s",
		name
	);

	DIR *dir = opendir(path);

	if (dir == NULL) {
		perror("hw: opendir");
		return;
	}

	printf("[%s]\n", name);

	struct dirent *entry;

	while ((entry = readdir(dir))  != NULL ) {
		if (entry->d_name[0] == '.')
			continue;

		printf(" %s\n", entry->d_name);
	}

	closedir(dir);
}

int linix_cmd_hw(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	list_class("net");
	list_class("drm");
	list_class("input");

	return 0;
}

LINIX_REGISTER_COMMAND("hw", linix_cmd_hw)
