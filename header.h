#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>

#define PROMPT "#csisfun$ "
#define BUFFSIZE 1024
#define UNUSED __attribute__((unused))

extern char **environ;

/**
 * struct data - program's data
 * @cmd: command
 * @last_exit_stat: last exit status
 * @argv: array
 * @flag: flag
 * @shell: shell name
 */
typedef struct data
{
	char **argv;
	const char *shell;
	char *cmd;
	int last_exit_stat;
	int flag;
} data;

/**
 * struct create - creates names and function
 * @cmd: command
 * @f: the create's function
 */
typedef struct create
{
	const char *cmd;
	void (*f)(data *t);
} create;

/* create.c */
int exec_create(data *t);
void create_exit(data *t);
void create_env(data *t);
void create_setenv(data *t);
void create_unsetenv(data *t);
void create_cd(data *t);

/* aide.c */
void _printf(const char *s);
void free_array(char **array);
void split(data *t, const char *delim);
void init(data *t, const char *shell);
void read_cmd(data *t);

/* aide2.c */
void _perror(const char *s1, const char *s2);
void _trim(char *s);
void *_realloc(void *p, unsigned int new_size);

/* handle.c */
void start_process(data *t);
void handler_sigint(int sg);
void exec(data *t);

/* path.c */
char *_getenv(char *n);
int _how(data *t);
char *create_new_entry(char *n, char *v);
char **_new_environ(char *n, char *v);
int _setenv(data *t, char *n, char *v);

/* strings.c */
unsigned int _strlen(char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcpy(char *d, const char *src);
char *_strcat(char *d, const char *src);

/* strings2.c */
char *_strdup(const char *s);
int _isnumber(const char *stat);
int _isdigit(int i);

#endif
