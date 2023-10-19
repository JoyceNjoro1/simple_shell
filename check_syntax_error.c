#include "main.h"

/**
 * count_repeated_char - Count the repetitions of a character
 *
 * @str: Input string
 * @index: Index
 *
 * Return: Number of repetitions
 */
int count_repeated_char(char *str, int index)
{
	if (*(str - 1) == *str)
		return (count_repeated_char(str - 1, index + 1));

	return (index);
}

/**
 * find_syntax_error - Find syntax errors in the input
 *
 * @str: Input string
 * @index: Index
 * @last_char: Last character read
 *
 * Return: Index of the error, 0 when there are no errors
 */
int find_syntax_error(char *str, int index, char last_char)
{
	int error_count;

	error_count = 0;

	if (*str == '\0')
		return (0);

	if (*str == ' ' || *str == '\t')
		return (find_syntax_error(str + 1, index + 1, last_char));

	if (*str == ';')
		if (last_char == '|' || last_char == '&' || last_char == ';')
			return (index);

	if (*str == '|')
	{
		if (last_char == ';' || last_char == '&')
			return (index);

		if (last_char == '|')
		{
			error_count = count_repeated_char(str, 0);
			if (error_count == 0 || error_count > 1)
				return (index);
		}
	}

	if (*str == '&')
	{
		if (last_char == ';' || last_char == '|')
			return (index);

		if (last_char == '&')
		{
			error_count = count_repeated_char(str, 0);
			if (error_count == 0 || error_count > 1)
				return (index);
		}
	}

	return (find_syntax_error(str + 1, index + 1, *str));
}

/**
 * find_first_char - Find the index of the first non-whitespace character
 *
 * @str: Input string
 * @index: Index
 *
 * Return: 1 if there is an error, 0 otherwise
 */
int find_first_char(char *str, int *index)
{
	for (*index = 0; str[*index]; *index += 1)
	{
		if (str[*index] == ' ' || str[*index] == '\t')
			continue;

		if (str[*index] == ';' || str[*index] == '|' || str[*index] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error_message - Print a syntax error message
 *
 * @data: Data structure
 * @str: Input string
 * @index: Index of the error
 * @is_first_error: Flag to control the error message
 *
 * Return: No return value
 */
void print_syntax_error_message(data_shell *data, char *str, int index, int is_first_error)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (str[index] == ';')
	{
		if (is_first_error == 0)
			msg = (str[index + 1] == ';' ? ";;" : ";");
		else
			msg = (str[index - 1] == ';' ? ";;" : ";");
	}

	if (str[index] == '|')
		msg = (str[index + 1] == '|' ? "||" : "|");

	if (str[index] == '&')
		msg = (str[index + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(data->counter);
	length = _strlen(data->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_for_syntax_error - Intermediate function to find and print a syntax error
 *
 * @data: Data structure
 * @str: Input string
 *
 * Return: 1 if there is an error, 0 otherwise
 */
int check_for_syntax_error(data_shell *data, char *str)
{
	int begin_index = 0;
	int first_char_result = 0;
	int error_index = 0;

	first_char_result = find_first_char(str, &begin_index);
	if (first_char_result == -1)
	{
		print_syntax_error_message(data, str, begin_index, 0);
		return (1);
	}

	error_index = find_syntax_error(str + begin_index, 0, *(str + begin_index));
	if (error_index != 0)
	{
		print_syntax_error_message(data, str, begin_index + error_index, 1);
		return (1);
	}

	return (0);
}

