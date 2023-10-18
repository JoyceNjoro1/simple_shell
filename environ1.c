#include "main.h"

/**
 * cmp_env_name - Compare environment variable names with the given name.
 * @nenv: Name of the environment variable
 * @name: Name to compare
 *
 * Return: 0 if they are not equal, otherwise returns a different value.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable to retrieve
 * @_environ: Environment variable array
 *
 * Return: Value of the environment variable if found, or NULL otherwise.
 */
char *_getenv(const char *name, char **_environ)
{
	char *env_ptr;
	int i, shift;

	env_ptr = NULL;
	shift = 0;

	for (i = 0; _environ[i]; i++)
	{
		shift = cmp_env_name(_environ[i], name);
		if (shift)
		{
			env_ptr = _environ[i];
			break;
		}
	}

	return (env_ptr + shift);
}

/**
 * _env - Print the environment variables.
 *
 * @datash: Data structure containing relevant information.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);

