#include "main.h"

/**
 * strcat_cd - Concatenates error message for the cd command.
 *
 * @datash: Data structure (directory)
 * @msg: Message to print
 * @error: Output error message
 * @line_count: Line counter
 * Return: Error message
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *line_count)
{
	char *illegal_flag;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, line_count);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);

	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - Error message for the cd command in the get_cd function.
 * @datash: Data structure (directory)
 * Return: Error message
 */
char *error_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *line_count, *msg;

	line_count = aux_itoa(datash->counter);

	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(line_count) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(line_count);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, line_count);

	free(line_count);

	return (error);
}

/**
 * error_not_found - Generic error message for "command not found."
 * @datash: Data structure (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *line_count;

	line_count = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(line_count);
	length += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(line_count);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, line_count);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(line_count);

	return (error);
}

/**
 * error_exit_shell - Generic error message for the "exit" command in get_exit.
 * @datash: Data structure (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *line_count;

	line_count = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(line_count);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(line_count);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, line_count);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(line_count);

	return (error);
}

