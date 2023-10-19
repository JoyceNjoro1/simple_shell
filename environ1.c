#include "main.h"

/**
 * cmp_env_name - Compare environment variable names with the name passed.
 *
 * @nenv: Name of the environment variable
 * @name: Name passed
 *
 * Return: 0 if they are not equal, otherwise the position of inequality.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    for (i = 0; nenv[i] != '='; i++)
    {
        if (nenv[i] != name[i])
        {
            return 0;
        }
    }

    return i + 1;
}

/**
 * _getenv - Get an environment variable's value.
 *
 * @name: Name of the environment variable
 * @_environ: Environment variable
 *
 * Return: Value of the environment variable if found, otherwise NULL.
 */
char *_getenv(const char *name, char **_environ)
{
    char *env_value;
    int i, position;

    env_value = NULL;
    position = 0;

    for (i = 0; _environ[i]; i++)
    {
        position = cmp_env_name(_environ[i], name);
        if (position)
        {
            env_value = _environ[i];
            break;
        }
    }

    return (env_value + position);
}

/**
 * _env - Print the environment variables.
 *
 * @datash: Data relevant.
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
        write(STDOUT_FILENO, "\n", 1);
    }
    datash->status = 0;

    return 1;
}

