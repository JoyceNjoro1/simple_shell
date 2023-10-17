#include "main.h"
/**
 * cmp_env_name - compares env variables and names
 * with the name passed.
 * @nenv:environment variable name
 * @name: the name passed
 *
 * Return: 0 if are not equal.else another value
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int k;

	for (k = 0; nenv[k] != '='; k++)
	{
		if (nenv[k] != name[k])
		{
			return (0);
		}
	}

	return (k + 1);
}

/**
 * _getenv - get an env variable
 * @name: the variable's name
 * @_environ: the environment variable
 *
 * Return: environment variable's name if found.
 * elsereturns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int k, mov;

	ptr_env = NULL;
	mov = 0;
	for (k = 0; _environ[k]; k++)
	{
		mov = cmp_env_name(_environ[k], name);
		if (mov)
		{
			ptr_env = _environ[k];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the env var
 *
 * @datash: data relevant.
 * Return: 1 on success, else any other.
 */
int _env(data_shell *datash)
{
	int x, y;

	for (x = 0; datash->_environ[x]; x++)
	{

		for (y = 0; datash->_environ[x][y]; y++)
			;

		write(STDOUT_FILENO, datash->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
