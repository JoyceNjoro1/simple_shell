#include "main.h"

/**
 * get_help - Retrieve help messages based on the specified built-in command.
 *
 * @data: Data structure containing arguments and input.
 * 
 * Return: Always returns 0.
 */
int get_help(data_shell *data)
{
	if (data->args[1] == 0)
		auxiliary_help_general();
	else if (_strcmp(data->args[1], "setenv") == 0)
		auxiliary_help_setenv();
	else if (_strcmp(data->args[1], "env") == 0)
		auxiliary_help_env();
	else if (_strcmp(data->args[1], "unsetenv") == 0)
		auxiliary_help_unsetenv();
	else if (_strcmp(data->args[1], "help") == 0)
		auxiliary_help();
	else if (_strcmp(data->args[1], "exit") == 0)
		auxiliary_help_exit();
	else if (_strcmp(data->args[1], "cd") == 0)
		auxiliary_help_cd();
	else if (_strcmp(data->args[1], "alias") == 0)
		auxiliary_help_alias();
	else
		write(STDERR_FILENO, data->args[0], _strlen(data->args[0]));

	data->status = 0;
	return (0);
}

