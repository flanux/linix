#include <unistd.h>
#include <errno.h>

#include <linix/io.h>

ssize_t linix_write_all(
	int fd,
	const void *buffer,
	size_t count
)
{
	const char *p = buffer;

	size_t remaining = count;

	while (remaining > 0) {
		ssize_t written = 
			write(fd, p, remaining);

		if (written == -1) {
			if (errno == EINTR)
				continue;

			return -1;
		}

		if (written == 0)
			return -1;

		p += written;

		remaining -= written;
	}
	
	return count;
}
