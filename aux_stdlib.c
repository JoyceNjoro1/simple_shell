#include "main.h"

/**
 * get_number_length - Get the length of an integer.
 *
 * @n: Integer to determine the length of.
 *
 * Return: Length of the integer.
 */
int get_number_length(int n)
{
	unsigned int absolute_n;
	int length = 1;

	if (n < 0)
	{
		length++;
		absolute_n = n * -1;
	}
	else
	{
		absolute_n = n;
	}

	while (absolute_n > 9)
	{
		length++;
		absolute_n = absolute_n / 10;
	}

	return length;
}

/**
 * int_to_string - Convert an integer to a string.
 *
 * @n: Integer to convert.
 *
 * Return: The string representation of the integer.
 */
char *int_to_string(int n)
{
	unsigned int absolute_n;
	int length = get_number_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		absolute_n = n * -1;
		buffer[0] = '-';
	}
	else
	{
		absolute_n = n;
	}

	length--;
	do {
		*(buffer + length) = (absolute_n % 10) + '0';
		absolute_n = absolute_n / 10;
		length--;
	}
	while (absolute_n > 0);

	return buffer;
}

/**
 * string_to_int - Convert a string to an integer.
 *
 * @s: Input string.
 *
 * Return: The integer representation of the string.
 */
int string_to_int(char *s)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		result = result + ((*(s + i) - '0') * multiplier);
		multiplier /= 10;
	}
	return result * sign;
}

