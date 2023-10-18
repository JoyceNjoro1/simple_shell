#include "main.h"

/**
 * errorEnv - Error message for 'env' in getEnv.
 *
 * @datash: Relevant data (counter, arguments).
 * Return: Error message.
 */
char *errorEnv(data_shell *datash)
{
	int length;
	char *error;
	char *verStr;
	char *message;

	verStr = auxItoa(datash->counter);
	message = ": Unable to modify the environment\n";
	length = _strlen(datash->av[0]) + _strlen(verStr);
	length += _strlen(datash->args[0]) + _strlen(message) + 4;
	error = malloc(sizeof(char) * (length + 1);

	if (error == 0)
	{
		free(error);
		free(verStr);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, verStr);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, message);
	_strcat(error, "\0");
	free(verStr);

	return (error);
}

/**
 * errorPath126 - Error message for 'path' and permission denied (exit status 126).
 *
 * @datash: Relevant data (counter, arguments).
 * Return: The error string.
 */
char *errorPath126(data_shell *datash)
{
	int length;
	char *verStr;
	char *error;

	verStr = auxItoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(verStr);
	length += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1);

	if (error == 0)
	{
		free(error);
		free(verStr);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, verStr);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(verStr);

	return (error);
}

