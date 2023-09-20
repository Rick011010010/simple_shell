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

/**
 * data - struct holding program's data
 * @prgNam: program's name
 * @linpntr: line pointer
 * @cmd: command line tokenized
 * @envp: environment
 */
typedef struct data_t
{
	char *prgNam;
	char **argv;
	char *linpntr;
	char **cmd;
	int cmdSize;
	int cmdCounter;
	char **envp;
	char **alias;
	int flag;
	int modo;
	char *pewd;
} data_t;

/**
 * create_t - creates names and function
 * @cmd: command
 * @f: the create's function
 */
typedef struct create_t
{
	char *cmd;
	int (*f)(data_t*, int);
} create_t;

/* create.c */
int exec_create(data *t);
void create_exit(data *t);
void create_env(data *t);
void create_setenv(data *t);
void create_unsetenv(data *t);
void create_cd(data *t);

/* aide.c */
void _printf(const char *s);
void free(char **array);
void split(data *t, const char *delim);
void init(data *t, const char *shell);
void read(data *t);

/* aide2.c */
void _perror(const char *s1, const char *s2);
void _trim(char *s);
void *_realloc(void *p, unsigned int new_size);

/* handle.c */
void start_process(data *t);
void handler_sigint(int sg);
void _exec(data *t);

/* path.c */
char *_getenv(char *n);
int _how(data *t);
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
