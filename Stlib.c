#include "main.h"

/**
 * get_length - Get the length of an integer.
 * @n: The integer.
 *
 * Return: The length of the integer.
 */
int get_length(int n)
{
	unsigned int positive_n;
	int length = 1;

	if (n < 0)
	{
		length++;
		positive_n = n * -1;
	}
	else
	{
		positive_n = n;
	}

	while (positive_n > 9)
	{
		length++;
		positive_n = positive_n / 10;
	}

	return (length);
}

/**
 * int_to_str - Converts an integer to a string.
 * @n: The integer to be converted.
 *
 * Return: A dynamically allocated string representation of the integer.
 */
char *int_to_str(int n)
{
	unsigned int positive_n;
	int length = get_length(n);
	char *str;

	str = malloc(sizeof(char) * (length + 1));
	if (str == 0)
		return (NULL);

	*(str + length) = '\0';

	if (n < 0)
	{
		positive_n = n * -1;
		str[0] = '-';
	}
	else
	{
		positive_n = n;
	}

	length--;

	do {
		*(str + length) = (positive_n % 10) + '0';
		positive_n = positive_n / 10;
		length--;
	} while (positive_n > 0);

	return (str);
}

/**
 * string_to_int - Converts a string to an integer.
 * @s: The input string.
 *
 * Return: The integer converted from the string.
 */
int string_to_int(char *s)
{
	unsigned int count = 0, digits = 0, result = 0, sign = 1, multiplier = 1, i;

	while (*(s + count) != '\0')
	{
		if (digits > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (digits > 0)
				multiplier *= 10;
			digits++;
		}
		count++;
	}

	for (i = count - digits; i < count; i++)
	{
		result = result + ((*(s + i) - '0') * multiplier);
		multiplier /= 10;
	}

	return (result * sign);
}

