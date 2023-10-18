#include "main.h"

/**
 * cd_shell - Change the current directory
 *
 * @datash: Data structure containing relevant information
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *new_directory;
	int is_home, is_tilde, is_double_dash;

	new_directory = datash->args[1];

	if (new_directory != NULL)
	{
		is_home = _strcmp("$HOME", new_directory);
		is_tilde = _strcmp("~", new_directory);
		is_double_dash = _strcmp("--", new_directory);
	}

	if (new_directory == NULL || !is_home || !is_tilde || !is_double_dash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", new_directory) == 0)
	{
		cd_to_previous(datash);
		return (1);
	}

	if (_strcmp(".", new_directory) == 0 || _strcmp("..", new_directory) == 0)
	{
		cd_to_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}

