#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <linix/command.h>

static void print_namespace(const char *name)
{
	char path[128];
	char target[256];

	snprintf(
		path,
		sizeof(path),
		"/proc/self/ns/%s",
		name
	);

	ssize_t n = readlink(
		path,
		target,
		sizeof(target) - 1
	);

	if (n==-1) {
		perror(name);
		return;
	}

	target[n] = '\0';

	printf(
		"%-8s %s\n",
		name,
		target
	);
}

int linix_cmd_ns(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	print_namespace("pid");
	print_namespace("mnt");
	print_namespace("net");
	print_namespace("uts");
	print_namespace("ipc");
	print_namespace("user");

	return 0;
}

LINIX_REGISTER_COMMAND("ns", linix_cmd_ns)
