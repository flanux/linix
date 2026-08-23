#include <stdio.h>

#include <linix/error.h>

void linix_perror(const char *command)
{
	fprintf(stderr, "linix %s: ", command);
	perror(NULL);
}
