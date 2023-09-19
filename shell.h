#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int isCmd(info_t *, char *);
char *dupCha(char *, int, int);
char *findPath(info_t *, char *, char *);

int loophsh(char **);

void Eputs(char *);
int Eputchar(char);
int Putfd(char c, int fd);
int Putsfd(char *str, int fd);

int string_length(char *);
int string_compare(char *, char *);
char *starts_with_string(const char *, const char *);
char *string_concatenate(char *, char *);

char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int write_character(char);

char *_strncpy4(char *, char *, int);
char *_strncat4(char *, char *, int);
char *_strchr4(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void BEffree(char **);
void *Realloc1(void *, unsigned int, unsigned int);

int befree2(void **);

int interactive1(info_t *);
int is_delim1(char, char *);
int _isalpha1(int);
int _atoi1(char *);

int _erratoi3(char *);
void print_error3(info_t *, char *);
int print_d3(int, int);
char *convert_number3(long int, int, int);
void remove_comments3(char *);

int _myexit2(info_t *);
int _mycd2(info_t *);
int _myhelp2(info_t *);

int Myhtr(info_t *);
int Myalias(info_t *);

ssize_t getInput(info_t *);
int Getline(info_t *, char **, size_t *);
void _sigintHandler(int);

void Clear_info(info_t *);
void Set_info(info_t *, char **);
void Free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int Myenv(info_t *);
int Mysetenv(info_t *);
int Myunsetenv(info_t *);
int PopEnvList(info_t *);

char **getEnviron(info_t *);
int Unsetenv(info_t *, char *);
int Setenv(info_t *, char *, char *);

char *getHistoryFile(info_t *info);
int writeFistory(info_t *info);
int readFistory(info_t *info);
int buildHistory_list(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

list_t *add_node4(list_t **, const char *, int);
list_t *add_node_end4(list_t **, const char *, int);
size_t print_ls4(const list_t *);
int delete_node4(list_t **, unsigned int);
void free_l4(list_t **);

size_t listLen(const list_t *);
char **listToStr(list_t *);
size_t printList(const list_t *);
list_t *nodeStarts_with(list_t *, char *, char);
ssize_t getNode(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

