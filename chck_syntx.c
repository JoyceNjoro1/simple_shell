#include "main.h"

/**
 * repeated_char - show number of times a chr is repeated
 *
 * @input: the input string
 * @i: iterator
 * Return: no of time repeated
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - looks for  syntax errors
 *
 * @input:the  input string
 * @i: index
 * @last: last char to read
 * Return: index of err. else 0 no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int cnt;

	cnt = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			cnt = repeated_char(input, 0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			cnt = repeated_char(input, 0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - gets the index of the 1st char
 *
 * @input: the input string
 * @i: index
 * Return: 1 if there is an error. else 0 .
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints a syntax err
 *
 * @datash: data structure
 * @input: the input string
 * @i: index of the error
 * @bool: to control msg err
 * Return: null
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int lngth;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	lngth = _strlen(datash->av[0]) + _strlen(counter);
	lngth += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (lngth + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, lngth);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - other function to
 * find & print a syntax err
 *
 * @datash: data structure
 * @input: the  input string
 * Return: 1 if there is an error. else 0
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int bgin = 0;
	int f_char = 0;
	int x = 0;

	f_char = first_char(input, &bgin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, bgin, 0);
		return (1);
	}

	x = error_sep_op(input + bgin, 0, *(input + bgin));
	if (x != 0)
	{
		print_syntax_error(datash, input, bgin + x, 1);
		return (1);
	}

	return (0);
}
