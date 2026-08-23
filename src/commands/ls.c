#include <stdio.h>
#include <dirent.h>

#include <linix/command.h>
#include <linix/error.h>

int linix_cmd_ls(int argc, char **argv)
{
	const char *path = ".";

	if (argc >=2)
		path = argv[1];

	DIR *dir = opendir(path);

	if (dir == NULL) {
		linix_perror("ls");
		return 1;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) 
		printf("%s\n", entry->d_name);

	closedir(dir);

	return 0;
}

LINIX_REGISTER_COMMAND("ls", linix_cmd_ls)
