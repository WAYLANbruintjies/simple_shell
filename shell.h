#ifndef SHELL_H
#define SHELL_H
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"
#define INFO_INIT	{NULL, 0}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

/* def READ/WRITE buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* def command chaining */
#define CMD_CHAIN       3
#define CMD_AND         2
#define CMD_OR          1
#define CMD_NORM        0

/* def convert_number() FUNCTION */
#define CONVERT_UNSIGNED        2
#define CONVERT_LOWERCASE       1

/* def getline() FUNCTION */
#define USE_GETLINE 0
#define USE_STRTOK 0


/**
 * struct liststr - Singly linked list
 * @num: number fieldset
 * @str: string to be computed
 * @next: points to the next following node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct builtin - Builtin functions and strings
 * @type: command flag
 * @func: the function to be computed
 */
typedef struct builtin
{
	char *type;
	int (*func)(ino_t *);
} builtin_table;

/**
 * struct passinfo - Arguements to pass into a function for a
 * uniform prototype for function pointer struct
 * @arg: a getline generated string containing arguements
 * @argv: argument vector
 * @path: a string path
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()
 * @linecount_flag: line of input (if active)
 * @fname: the program filename
 * @env: local copy of environ
 * @environ: custom modified copy of environ
 * @history: history
 * @alias: alias
 * @env_changed: active when environ was changed
 * @status: return the status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the file disk to read line input from
 * @histcount: history line number count
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

extern char **environ;
int _putchar(char);
void _puts(char *);
int _atoi(char *);
int _isalpha(int);
int is_delim(char, char *);
int interactive(info_t *);
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
int find_builtin(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int loophsh(char **);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
int bfree(void **);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
char **strtow(char *, char *);
char **strtow2(char *, char);
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);
int _myhistory(info_t *);
int _myalias(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _myunsetenv(info_t *);
int _mysetenv(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
char **list_to_strings(list_t *);
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t print_list(const list_t *);
char *get_history_file(info_t *info);
int read_history(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

#endif /* SHELL_H */
