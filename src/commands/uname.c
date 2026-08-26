#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/utsname.h>

#include <linix/command.h>

int linix_cmd_uname(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	struct utsname info;

	if (uname(&info) == -1) {
		perror("uname");
		return 1;
	}

	printf("sysname: %s\n", info.sysname);
	printf("nodename: %s\n", info.nodename);
	printf("release: %s\n", info.release);
	printf("version: %s\n", info.version);
	printf("machine: %s\n", info.machine);

	return 0;
}

LINIX_REGISTER_COMMAND("uname", linix_cmd_uname)
