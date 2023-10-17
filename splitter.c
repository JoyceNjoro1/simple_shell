#include "main.h"
/**
 * swap_char - it swap the unprinted strings
 *
 * @input: the input string
 * @bool: the type of swap
 * Return: the swapped string
 */
char *swap_char(char *input, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == '|')
			{
				if (input[j + 1] != '|')
					input[j] = 16;
				else
					j++;
			}

			if (input[j] == '&')
			{
				if (input[j + 1] != '&')
					input[j] = 12;
else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input[j]; j++)
		{
			input[j] = (input[j] == 16 ? '|' : input[j]);
			input[j] = (input[j] == 12 ? '&' : input[j]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators to the comand line
 *
 * @head_s: head of the separator 
 * @head_l: head of the command lines list
 * @input: it is the input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int k;
	char *line;

	input = swap_char(input, 0);

	for (k = 0; input[k]; k++)
	{
		if (input[k] == ';')
			add_sep_node_end(head_s, input[k]);

		if (input[k] == '|' || input[k] == '&')
		{
			add_sep_node_end(head_s, input[k]);
			k++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next comand
 *
 * @list_s: the separator
 * @list_l:the  command line
 * @datash: data stru_cture
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits commands according to
 * the separator and executes them
 *
 * @datash: the data structure
 * @input: the input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenize the input string
 *
 * @input: string to be tokenized.
 * Return: tokenized string.
 */
char **split_line(char *input)
{
	size_t b_size;
	size_t k;
	char **tokens;
	char *token;

	b_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (b_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (k = 1; token != NULL; k++)
	{
		if (k == b_size)
		{
			b_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, k, sizeof(char *) * b_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[k] = token;
	}

	return (tokens);
}
