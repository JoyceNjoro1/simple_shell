#include "main.h"

/**
 * is_cdir - checks :if is in the current directory or not.
 * @path: type char pointer char.
 * @i: type int index pointer.
 * Return: 1 if the path can nbe searched in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a cmd
 *
 * @cmd: the command to be executed
 * @_environ: environment variable
 * Return: location of the cmd.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int leng_dir, leng_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		leng_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			leng_dir = _strlen(token_path);
			dir = malloc(leng_dir + leng_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if  cmd is  executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable,else other number
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int j;
	char *input;

	input = datash->args[0];
	for (j = 0; input[j]; j++)
	{
		if (input[j] == '.')
		{
			if (input[j + 1] == '.')
				return (0);
			if (input[j + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[j] == '/' && j != 0)
		{
			if (input[j + 1] == '.')
				continue;
			j++;
			break;
		}
		else
			break;
	}
	if (j == 0)
		return (0);

	if (stat(input + j, &st) == 0)
	{
		return (j);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user if the user is authorized
 *
 * @dir: destination dir
 * @datash: data structure
 * Return: 1 if there is an error, 0 else
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes cmds
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success, else any number.
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
