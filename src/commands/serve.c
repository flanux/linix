#include <arpa/inet.h>

#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/epoll.h>

#include <linix/command.h>

static int create_server(void)
{
	int fd = socket(
		AF_INET,
		SOCK_STREAM,
		0
	);

	if (fd == -1) return -1;

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(9000),
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK)
	};

	if (bind(
		fd,
		(struct sockaddr *)&addr,
		sizeof(addr)
	) == -1) {
		close(fd);
		return -1;
	}

	if (listen(fd, 16) == -1) {
		close(fd);
		return -1;
	}

	return fd;
}

int linix_cmd_serve(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int server_fd = create_server();

	if (server_fd == -1) {
		perror("serve");
		return 1;
	}

	int epfd = epoll_create1(0);

	if (epfd == -1) {
		perror("epoll_create1");
		close(server_fd);
		return 1;
	}

	struct epoll_event event = {
		.events = EPOLLIN,
		.data.fd = server_fd
	};

	if (epoll_ctl(
		epfd,
		EPOLL_CTL_ADD,
		server_fd,
		&event
	) == -1) {
		perror("epoll_ctl");
		close(epfd);
		close(server_fd);
		return 1;
	}

	printf("linix serve: listening on 127.0.0.1:9000\n");

	for (;;) {
		struct epoll_event events[16];

		int n = epoll_wait(
			epfd,
			events,
			16,
			-1
		);

		if (n==-1) {
			perror("epoll_wait");
			break;
		}

		for (int i=0; i<n; i++) {
			int fd = events[i].data.fd;

			if (fd == server_fd) {
				int client_fd = accept(
					server_fd,
					NULL,
					NULL
				);

				if (client_fd == -1 ) {
					perror("accept");
					continue;
				}

				struct epoll_event client_event = {
					.events = EPOLLIN,
					.data.fd = client_fd
				};

				epoll_ctl(
					epfd,
					EPOLL_CTL_ADD,
					client_fd,
					&client_event
				);

				printf("client connected: fd=%d\n", client_fd);
			} else {
				char buffer[256];

				ssize_t bytes = read(
					fd,
					buffer,
					sizeof(buffer) -1
				);

				if (bytes <= 0) {
					close(fd);
					continue;
				}

				buffer[bytes] = '\0';

				printf("client %d: %s", fd, buffer);

				write(
					fd,
					"got it\n",
					7
				);
			}
		}
	}

	close(epfd);
	close(server_fd);

	return 0;
}

LINIX_REGISTER_COMMAND("serve", linix_cmd_serve)
