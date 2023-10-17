#ifndef  _MAIN_H_
#define  _MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter 
* @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

int cd_shell(data_shell *datash);
void cd_to_home(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
int exit_shell(data_shell *datash);
int exec_line(data_shell *datash);
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);
int cmp_env_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
char *copy_info(char *name, char *value);
int _unsetenv(data_shell *datash);
int _setenv(data_shell *datash);
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input)
char *without_comment(char *in);
void shell_loop(data_shell *datash);
int (*get_builtin(char *cmd))(data_shell *);
int get_error(data_shell *datash, int eval);
int get_help(data_shell *datash);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void get_sigint(int sig);

#endif
