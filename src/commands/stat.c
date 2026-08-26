#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/stat.h>

#include <linix/command.h>

static void print_stat(const char *path)
{
	struct stat info;

	if (stat(path, &info) == -1) {
		perror("stat");
		return;
	}

	printf("path: %s\n", path);
	printf("size: %ld\n", info.st_size);
	printf("mode: %o\n", info.st_mode & 07777);
	printf("uid: %u\n", info.st_uid);
	printf("gid: %u\n", info.st_gid);
	printf("inode: %lu\n", info.st_ino);
	printf("links: %lu\n", info.st_nlink);
}

int linix_cmd_stat(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: stat <path>\n");
		return 1;
	}

	print_stat(argv[1]);

	return 0;
}

LINIX_REGISTER_COMMAND("stat", linix_cmd_stat)
