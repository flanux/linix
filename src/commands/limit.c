#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <linix/command.h>

static int create_group(const char *name)
{
	char path[256];

	snprintf(
		path,
		sizeof(path),
		"/sys/fs/cgroup/%s",
		name
	);

	if (mkdir(path, 0755) == -1 ) {
		perror("limit: mkdir");
		return -1;
	}

	printf("created group: %s\n", path);

	return 0;
}

static int add_process(const char *name, const char *pid)
{
	char path[256];

	snprintf(
		path,
		sizeof(path),
		"/sys/fs/cgroup/%s/cgroup.procs",
		name
	);

	FILE *file = fopen(path, "w");

	if (file == NULL) {
		perror("limit: cgroup.procs");
		return -1;
	}

	fprintf(file, "%s\n", pid);

	fclose(file);

	printf("added PID %s to cgroup %s\n", pid, name);

	return 0;
}

int linix_cmd_limit(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: limit <pid>\n");
		return 1;
	}

	if (create_group("linix") == -1) {
		return 1;
	}
	
	if (add_process("linix", argv[1]) == -1) {
		return 1;
	}
	
	return 0;
}

LINIX_REGISTER_COMMAND("limit", linix_cmd_limit)
