#include "main.h"

/**
 * copy_info - Create a copy of the name
 * @name: Name (environment variable or alias)
 * @value: Value (environment variable or alias)
 *
 * Return: New environment variable
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - Set an environment var
 *
 * @name: Name of the environment var
 * @value: Value of the environment var
 * @datash: Data structure containing the environ
 * Return: void
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *current_var, *current_name;

	for (i = 0; datash->_environ[i]; i++)
	{
		current_var = _strdup(datash->_environ[i]);
		current_name = _strtok(current_var, "=");
		if (_strcmp(current_name, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(current_name, value);
			free(current_var);
			return;
		}
		free(current_var);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - Set an environment var
 *
 * @datash: Data structure containing the environ
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - Delete an environment var
 *
 * @datash: Data structure containing the environ var
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *current_var, *current_name;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		current_var = _strdup(datash->_environ[i]);
		current_name = _strtok(current_var, "=");
		if (_strcmp(current_name, datash->args[1]) == 0)
		{
			k = i;
		}
		free(current_var);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
