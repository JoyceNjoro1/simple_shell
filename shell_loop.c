#include "main.h"

/**
 * remove_comments - Remove comments from the input.
 *
 * @input: Input string
 * Return: Input string without comments
 */
char *remove_comments(char *input)
{
	int i, last_space;

	last_space = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return NULL;
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				last_space = i;
		}
	}

	if (last_space != 0)
	{
		input = _realloc(input, i, last_space + 1);
		input[last_space] = '\0';
	}

	return input;
}

/**
 * run_shell - Main shell loop.
 *
 * @datash: Data relevant (av, input, args)
 * Return: No return value.
 */
void run_shell(data_shell *datash)
{
	int is_running, is_eof;
	char *input;

	is_running = 1;
	while (is_running)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_input(&is_eof);
		if (is_eof != -1)
		{
			input = remove_comments(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replace_variables(input, datash);
			is_running = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			is_running = 0;
			free(input);
		}
	}
}

