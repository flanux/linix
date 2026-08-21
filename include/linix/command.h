#ifndef LINIX_COMMAND_H
#define LINIX_COMMAND_H

typedef int (*LinixCommandFn)(int argc, char **argv);

typedef struct {
	const char *name;
	LinixCommandFn fn;
} LinixCommand;

int linix_cmd_pwd(int argc, char **argv);
int linix_cmd_cat(int argc, char **argv);
int linix_cmd_echo(int argc, char **argv);
int linix_cmd_touch(int argc, char **argv);
int linix_cmd_mkdir(int argc, char **argv);
int linix_cmd_rm(int argc, char **argv);
int linix_cmd_ls(int argc, char **argv);

#endif
