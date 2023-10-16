#include "main.h"
#include "string.h"

/**
 * cd_shell - Change the current directory based on input
 *
 * @datash: A pointer to data relevant to the shell
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *target_dir;
	int is_home, is_home2, is_ddash;

	target_dir = datash->args[1];

	if (target_dir != NULL)
	{
		is_home = strcmp("$HOME", target_dir);
		is_home2 = strcmp("~", target_dir);
		is_ddas =_strcmp("--", target_dir);
	}

	if (target_dir == NULL || !is_home || !is_home2 || !is_ddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", target_dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", target_dir) == 0 || _strcmp("..", target_dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}

