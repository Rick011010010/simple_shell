/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for revert_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/* toem_shloop.c */
int hsh(info_t *, char **);
int builtin_finder(info_t *);
void comand_find(info_t *);
void cmd_fork(info_t *);

/* toem_parser.c */
int command_is(info_t *, char *);
char *chars_duplicate(char *, int, int);
char *find_path(info_t *, char *, char *);

/* hsh_loop.c */
int hsh_loop(char **);

/* toem_errors.c */
void _input(char *);
int _charputs(char);
int _rgputs(char c, int fd);
int _inputsrg(char *str, int fd);

/* toem_string.c */
int str_lenght(char *);
int str_computed(char *, char *);
char *begin(const char *, const char *);
char *cat_st(char *, char *);

/* toem_string1.c */
char *copy_st(char *, char *);
char *double_st(const char *);
void put_st(char *);
int putrg_str(char);

/* toem_exits.c */
char *cprg_st(char *, char *, int);
char *catrg_st(char *, char *, int);
char *chrfg_st(char *, char);

/* toem_tokenizer.c */
char **torg_st(char *, char *);
char **wrg_st(char *, char);

/* toem_realloc.c */
char *strg_mem(char *, char, unsigned int);
void frg_st(char **);
void *_locrg(void *, unsigned int, unsigned int);

/* toem_memory.c */
int forfree(void **);

/* toematoi_is.c */
int inter_active(info_t *);
int delim_is(char, char *);
int alpha_is(int);
int atoi_is(char *);

/* toem_errors1.c */
int toi_err(char *);
void err_rg(info_t *, char *);
int dup_prist(int, int);
char *revert_num(long int, int, int);
void cmt_rm(char *);

/* toem_builtin.c */
int scaprg(info_t *);
int cmdrt_my(info_t *);
int hand_st(info_t *);

/* toem_builtin1.c */
int title_my(info_t *);
int alias_chat(info_t *);

/*toem_getline.c */
ssize_t rginp_get(info_t *);
int give_line(info_t *, char **, size_t *);
void handle_rgst(int);

/* toem_getinfo.c */
void info_rgef(info_t *);
void in_forgst(info_t *, char **);
void avail_inf(info_t *, int);

/* toem_environ.c */
char *envst_get(info_t *, const char *);
int myst_en(info_t *);
int stenv_mys(info_t *);
int myrt_enven(info_t *);
int listpop_env(info_t *);

/* toem_getenv.c */
char **ench_get(info_t *);
int set_envun(info_t *, char *);
int liverg_set(info_t *, char *, char *);

/* toem_history.c */
char *getdf_all(info_t *info);
int his_fgwrite(info_t *info);
int his_rd(info_t *info);
int bui_ls_his(info_t *info, char *buf, int linecount);
int renth_tr(info_t *info);

/* toem_lists.c */
list_t *nd_addth(list_t **, const char *, int);
list_t *enad_notr(list_t **, const char *, int);
size_t ls_printdf(const list_t *);
int remove_nd_in(list_t **, unsigned int);
void li_nd_free(list_t **);

/* toem_lists1.c */
size_t long_strze(const list_t *);
char **chan_to_str(list_t *);
size_t lesta_at_pint(const list_t *);
list_t *bestr_nd(list_t *, char *, char);
ssize_t in_deffer(list_t *, list_t *);

/* toem_vars.c */
int chan_is_available(info_t *, char *, size_t *);
void chan_is_check(info_t *, char *, size_t *, size_t, size_t);
int alstr_rep(info_t *);
int rp_variables(info_t *);
int st_variables(char **, char *);

#endif
