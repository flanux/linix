#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <linix/event.h>

struct LinixEventLoop {
	int epfd;
};

LinixEventLoop *linix_event_create(void)
{
	LinixEventLoop *loop = malloc(sizeof(*loop));

	if (!loop)
		return NULL;

	loop->epfd = epoll_create1(0);

	if (loop->epfd == -1) {
		free(loop);
		return NULL;
	}

	return loop;
}

void linix_event_destroy(LinixEventLoop *loop)
{
	if (!loop)
		return;

	close(loop->epfd);
	free(loop);
}

int linix_event_add(
	LinixEventLoop *loop,
	int fd,
	unsigned events
)
{
	struct epoll_event event = {
		.events = events,
		.data.fd = fd
	};

	return epoll_ctl(
		loop->epfd,
		EPOLL_CTL_ADD,
		fd,
		&event
	);
}

int linix_event_wait(
	LinixEventLoop *loop,
	LinixEvent *events,
	size_t max_events
)
{
	struct epoll_event ready[16];

	if (max_events > 16)
		max_events = 16;

	int count = epoll_wait(
		loop->epfd,
		ready,
		(int)max_events,
		-1
	);

	if (count == -1)
		return -1;

	for (int i=0; i<count; i++) {
		events[i].fd = ready[i].data.fd;
		events[i].events = ready[i].events;
	}

	return count;
}
