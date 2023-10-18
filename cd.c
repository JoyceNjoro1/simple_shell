#include "main.h"

/**
 * cd_dot - Change to the parent directory
 *
 * @datash: Data structure containing relevant information
 * Return: No return value
 */
void cd_dot(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *directory, *copied_current_path, *copied_strtok_path;

	getcwd(current_path, sizeof(current_path));
	copied_current_path = _strdup(current_path);
	set_environment_variable("OLDPWD", copied_current_path, datash);
	directory = datash->args[1];

	if (_strcmp(".", directory) == 0)
	{
		set_environment_variable("PWD", copied_current_path, datash);
		free(copied_current_path);
		return;
	}

	if (_strcmp("/", copied_current_path) == 0)
	{
		free(copied_current_path);
		return;
	}

	copied_strtok_path = copied_current_path;
	rev_string(copied_strtok_path);
	copied_strtok_path = _strtok(copied_strtok_path, "/");
	if (copied_strtok_path != NULL)
	{
		copied_strtok_path = _strtok(NULL, "\0");

		if (copied_strtok_path != NULL)
			rev_string(copied_strtok_path);
	}

	if (copied_strtok_path != NULL)
	{
		chdir(copied_strtok_path);
		set_environment_variable("PWD", copied_strtok_path, datash);
	}
	else
	{
		chdir("/");
		set_environment_variable("PWD", "/", datash);
	}

	datash->status = 0;
	free(copied_current_path);
}

/**
 * cd_to - Change to a directory given by the user
 *
 * @datash: Data structure containing relevant directory information
 * Return: No return value
 */
void cd_to(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *directory, *copied_current_path, *copied_directory;

	getcwd(current_path, sizeof(current_path));
	directory = datash->args[1];

	if (chdir(directory) == -1)
	{
		get_error(datash, 2);
		return;
	}

	copied_current_path = _strdup(current_path);
	set_environment_variable("OLDPWD", copied_current_path, datash);
	copied_directory = _strdup(directory);
	set_environment_variable("PWD", copied_directory, datash);
	free(copied_current_path);
	free(copied_directory);
	datash->status = 0;

	chdir(directory);
}

/**
 * cd_previous - Change to the previous directory
 *
 * @datash: Data structure containing environment information
 * Return: No return value
 */
void cd_previous(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *previous_pwd, *previous_oldpwd, *copied_current_path, *copied_oldpwd;

	getcwd(current_path, sizeof(current_path));
	copied_current_path = _strdup(current_path);
	previous_oldpwd = get_environment_variable("OLDPWD", datash->_environ);

	if (previous_oldpwd == NULL)
		previous_oldpwd = copied_current_path;
	else
		previous_oldpwd = _strdup(previous_oldpwd);

	set_environment_variable("OLDPWD", copied_current_path, datash);

	if (chdir(previous_oldpwd) == -1)
		set_environment_variable("PWD", copied_current_path, datash);
	else
		set_environment_variable("PWD", previous_oldpwd, datash);

	previous_pwd = get_environment_variable("PWD", datash->_environ);
	write(STDOUT_FILENO, previous_pwd, _strlen(previous_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(copied_current_path);
	if (previous_oldpwd)
		free(previous_oldpwd);

	datash->status = 0;
	chdir(previous_pwd);
}

/**
 * cd_to_home - Change to the home directory
 *
 * @datash: Data structure containing environment information
 * Return: No return value
 */
void cd_to_home(data_shell *datash)
{
	char *current_path, *home;
	char copied_path[PATH_MAX];

	getcwd(copied_path, sizeof(copied_path));
	current_path = _strdup(copied_path);
	home = get_environment_variable("HOME", datash->_environ);

	if (home == NULL)
	{
		set_environment_variable("OLDPWD", current_path, datash);
		free(current_path);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(current_path);
		return;
	}

	set_environment_variable("OLDPWD", current_path, datash);
	set_environment_variable("PWD", home, datash);
	free(current_path);
	datash->status = 0;
}

