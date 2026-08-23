#include <stddef.h>

#include <linix/command.h>
#include <linix/registry.h>

extern const LinixCommand __start_linix_commands[];
extern const LinixCommand __stop_linix_commands[];

const LinixCommand *linix_commands(size_t *count)
{
	*count = __stop_linix_commands - __start_linix_commands;

	return __start_linix_commands;
}
