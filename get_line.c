#include "main.h"

/**
 * set_line_buffer - Assigns the line buffer for get_line
 *
 * @lineptr: Pointer to the buffer that stores the input string
 * @n: Size of line buffer
 * @buffer: String being assigned to line buffer
 * @j: Size of the string buffer
 */
void set_line_buffer(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * custom_get_line - Read input from a stream
 *
 * @lineptr: Pointer to the buffer that stores the input
 * @n: Size of lineptr buffer
 * @stream: Stream to read from
 *
 * Return: The number of bytes read
 */
ssize_t custom_get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char current_char = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (current_char != '\n')
	{
		i = read(STDIN_FILENO, &current_char, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = current_char;
		input++;
	}
	buffer[input] = '\0';
	set_line_buffer(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

