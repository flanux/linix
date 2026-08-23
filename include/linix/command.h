#ifndef LINIX_COMMAND_H
#define LINIX_COMMAND_H

typedef int (*LinixCommandFn)(int argc, char **argv);

typedef struct {
	const char *name;
	LinixCommandFn fn;
} LinixCommand;

#define LINIX_COMMAND(name, fn) \
	int fn(int argc, char **argv);

#include "linix/commands.def"

#undef LINIX_COMMAND

#endif
