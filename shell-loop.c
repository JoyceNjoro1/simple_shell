#include "main.h"

/**
 * without_comment - Remove comments from the input string.
 *
 * @in: Input string
 * Return: Input string without comments or NULL if the input starts with a comment.
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Main shell loop.
 *
 * @datash: Data structure containing relevant information (av, input, args).
 *
 * This function handles the main loop of the shell, reading input and executing commands.
 */
void shell_loop(data_shell *datash)
{
	int continue_loop, is_eof;
	char *input;

	continue_loop = 1;
	while (continue_loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&is_eof);
		if (is_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			continue_loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			continue_loop = 0;
			free(input);
		}
	}
}

