#include "main.h"

/**
 * swap_characters - Swap non-printed characters.
 *
 * @input: Input string
 * @swap_mode: Type of swap (0 for swap, 1 for reverse)
 * Return: Swapped string
 */
char *swap_characters(char *input, int swap_mode)
{
	int i;

	if (swap_mode == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_separator_and_lines - Add separators and command lines to the lists.
 *
 * @head_separator: Head of separator list
 * @head_lines: Head of command lines list
 * @input: Input string
 * Return: No return value
 */
void add_separator_and_lines(sep_list **head_separator, line_list **head_lines, char *input)
{
	int i;
	char *line;

	input = swap_characters(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separator_node_end(head_separator, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separator_node_end(head_separator, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_characters(line, 1);
		add_line_node_end(head_lines, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_to_next - Move to the next command line stored.
 *
 * @separator_list: Separator list
 * @lines_list: Command line list
 * @datash: Data structure
 * Return: No return value
 */
void go_to_next(sep_list **separator_list, line_list **lines_list, data_shell *datash)
{
	int loop_separator;
	sep_list *ls_separator;
	line_list *ls_lines;

	loop_separator = 1;
	ls_separator = *separator_list;
	ls_lines = *lines_list;

	while (ls_separator != NULL && loop_separator)
	{
		if (datash->status == 0)
		{
			if (ls_separator->separator == '&' || ls_separator->separator == ';')
				loop_separator = 0;
			if (ls_separator->separator == '|')
				ls_lines = ls_lines->next, ls_separator = ls_separator->next;
		}
		else
		{
			if (ls_separator->separator == '|' || ls_separator->separator == ';')
				loop_separator = 0;
			if (ls_separator->separator == '&')
				ls_lines = ls_lines->next, ls_separator = ls_separator->next;
		}
		if (ls_separator != NULL && !loop_separator)
			ls_separator = ls_separator->next;
	}

	*separator_list = ls_separator;
	*lines_list = ls_lines;
}

/**
 * execute_commands - Split command lines according to separators (;, |, &)
 * and execute them.
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 0 to exit, 1 to continue
 */
int execute_commands(data_shell *datash, char *input)
{
	sep_list *head_separator, *separator_list;
	line_list *head_lines, *lines_list;
	int loop;

	head_separator = NULL;
	head_lines = NULL;

	add_separator_and_lines(&head_separator, &head_lines, input);

	separator_list = head_separator;
	lines_list = head_lines;

	while (lines_list != NULL)
	{
		datash->input = lines_list->line;
		datash->args = split_input(datash->input);
		loop = execute_input(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_to_next(&separator_list, &lines_list, datash);

		if (lines_list != NULL)
			lines_list = lines_list->next;
	}

	free_separator_list(&head_separator);
	free_line_list(&head_lines);

	if (loop == 0)
		return 0;
	return 1;
}

/**
 * split_input - Tokenize the input string.
 *
 * @input: Input string.
 * Return: Array of tokens.
 */
char **split_input(char *input)
{
	size_t buffer_size;
	size_t i;
	char **tokens;
	char *token;

	buffer_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (buffer_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * buffer_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return tokens;
}

