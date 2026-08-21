#ifndef LINIX_IO_H
#define LINIX_IO_H

#include <stddef.h>
#include <sys/types.h>

ssize_t linix_write_all(
	int fd,
	const void *buffer,
	size_t count
);

#endif
