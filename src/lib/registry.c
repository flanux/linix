#include <stddef.h>

#include <linix/command.h>
#include <linix/registry.h>

#define LINIX_COMMAND(cmd_name, cmd_fn) \
	{.name = #cmd_name, .fn = cmd_fn },

static const LinixCommand commands[] = {
#include <linix/commands.def>
};

#undef LINIX_COMMAND

const LinixCommand *linix_commands(size_t *count)
{
	*count  = sizeof(commands) / sizeof(commands[0]);

	return commands;
}
