#include <stdio.h>
#include <dirent.h>

#include <linix/command.h>

int linix_cmd_ls(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	DIR *dir = opendir(".");

	if (dir == NULL) {
		perror("linix ls");
		return 1;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) 
		printf("%s\n", entry->d_name);

	closedir(dir);

	return 0;
}
