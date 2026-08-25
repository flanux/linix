#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <linix/command.h>

static int is_pid_name(const char *name)
{
	if (*name == '\0') {
		return 0;
	}

	for (const char *p = name; *p; p++) {
		if (!isdigit((unsigned char)*p)) {
			return 0;
		}
	}

	return 1;
}

static void print_process(const char  *pid)
{
	char path[512];

	snprintf(
		path,
		sizeof(path),
		"/proc/%s/status",
		pid
	);

	FILE *file = fopen(path, "r");

	if (file == NULL) {
		return;
	}

	char line[256];

	char name[128] = "";
	char state[128] = "";
	char ppid[32] = "";
	char rss[32] = "";

	while (fgets(
		line,
		sizeof(line),
		file
	) != NULL) {
		
		if (strncmp(
			line,
			"Name:",
			5
		) == 0) {
			sscanf(
				line+5,
				"%127s",
				name
			);
		} else if (strncmp(
			line,
			"State:",
			6
		) == 0) {
			sscanf(
				line + 6,
				"%127s",
				state
			);
		} else if (strncmp(
			line,
			"PPid:",
			5
		) == 0) {
			sscanf(
				line+5,
				"%31s",
				ppid
			);
		} else if (strncmp(
			line,
			"VmRSS:",
			6
		) == 0) {
			sscanf(
				line + 6,
				"%31s",
				rss
			);
		}
	}

	fclose(file);

	printf(
		"%-8s %-20s %-8s %-8s %-10s\n",
		pid,
		name,
		ppid,
		state,
		rss
	);
}

int linix_cmd_ps(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	DIR *dir = opendir("/proc");

	if (dir == NULL) {
		perror("ps: opendir");
		return 1;
	}

	printf(
		"%-8s %-20s %-8s %-8s %-10s\n",
		"PID",
		"NAME",
		"PPID",
		"STATE",
		"RSS(kb)"
	);

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL) {
		if (!is_pid_name(entry->d_name)) {
			continue;
		}

		print_process(entry->d_name);
	}


	closedir(dir);

	return 0;
}

LINIX_REGISTER_COMMAND("ps", linix_cmd_ps)
