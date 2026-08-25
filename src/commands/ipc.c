#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <linix/command.h>

static int create_socket(const char *path)
{
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (fd == -1) {
		perror("socket");
		return -1;
	}

	struct sockaddr_un addr = {
		.sun_family = AF_UNIX
	};

	strncpy(
		addr.sun_path,
		path,
		sizeof(addr.sun_path) - 1
	);

	unlink(path);

	if (bind(
		fd,
		(struct sockaddr *)&addr,
		sizeof(addr)
	) == -1) {
		perror("ipc: bind");
		close(fd);
		return -1;
	}

	if (listen(fd, 1) == -1) {
		perror("ipc: listen");
		close(fd);
		unlink(path);
		return -1;
	}

	return fd;
}

int linix_cmd_ipc(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	const char *path = "/tmp/linix.sock";

	int server = create_socket(path);

	if (server == -1) {
		perror("ipc: server");
		return 1;
	}

	printf("IPC server listening at %s\n", path);
	printf("Run: socat - UNIX-CONNECT:%s\n", path);

	int client = accept(server, NULL, NULL);

	if (client == -1) {
		perror("ipc: accept");
		close(server);
		unlink(path);
		return 1;
	}

	char buffer[256];

	ssize_t n = read(
		client,
		buffer,
		sizeof(buffer) - 1
	);

	if (n > 0) {
		buffer[n] = '\0';

		printf("received: %s", buffer);

		write(
			client,
			"hello from linix\n",
			17
		);
	}

	close(client);
	close(server);
	unlink(path);

	return 0;
}

LINIX_REGISTER_COMMAND("ipc", linix_cmd_ipc)
