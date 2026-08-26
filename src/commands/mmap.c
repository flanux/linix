#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include <linix/command.h>

static int map_memory(void)
{
	long page_size = sysconf(_SC_PAGESIZE);

	if (page_size == -1) {
		perror("mmap: sysconf");
		return -1;
	}

	void *memory = mmap(
		NULL,
		page_size,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1,
		0
	);

	if (memory == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	const char message[] = "hello from mapped memory\n";

	memcpy(
		memory,
		message,
		sizeof(message)
	);

	printf("%s", (char *)memory);

	printf(
		"addresss: %p\n",
		memory
	);

	printf(
		"page size: %ld\n",
		page_size
	);

	if (munmap(memory, page_size) == -1) {
		perror("mmap: munmap");
		return -1;
	}

	return 0;
}

int linix_cmd_mmap(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	return map_memory() == -1 ? 1 : 0;
}

LINIX_REGISTER_COMMAND("mmap", linix_cmd_mmap)
