#include <stddef.h>

#include <linix/command.h>
#include <linix/registry.h>

static const LinixCommand commands[] = {
	{
		.name = "pwd",
		.fn = linix_cmd_pwd
	},
	{
		.name = "cat",
		.fn = linix_cmd_cat
	},
	{
		.name = "echo",
		.fn = linix_cmd_echo
	},
	{
		.name = "touch",
		.fn = linix_cmd_touch
	},
	{
		.name = "mkdir",
		.fn = linix_cmd_mkdir
	},
	{
		.name = "rm",
		.fn = linix_cmd_rm
	},
	{
		.name = "ls",
		.fn = linix_cmd_ls
	},
	{
		.name = "cp",
		.fn = linix_cmd_cp
	},
	{
		.name = "mv",
		.fn = linix_cmd_mv
	}
};

const LinixCommand *linix_commands(size_t *count)
{
	*count  = sizeof(commands) / sizeof(commands[0]);

	return commands;
}
