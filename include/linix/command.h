#ifndef LINIX_COMMAND_H
#define LINIX_COMMAND_H

typedef int (*LinixCommandFn)(int argc, char **argv);

typedef struct {
	const char *name;
	LinixCommandFn fn;
} LinixCommand;

#define LINIX_REGISTER_COMMAND(cmd_name, cmd_fn) \
	static const LinixCommand linix_command_##cmd_fn \
	__attribute__((section("linix_commands"), used)) = { \
		.name = cmd_name, \
		.fn = cmd_fn \
	};
#endif
