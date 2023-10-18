#include "main.h"
#include "string.h"

/**
 * _strdup - Duplicates a string in the heap memory.
 * @s: The string to be duplicated.
 * Return: A duplicated string.
 */
char *_strdup(const char *s)
{
    char *duplicate;
    size_t length;

    length = strlen(s);
    duplicate = malloc(sizeof(char) * (length + 1));
    if (duplicate == NULL)
        return (NULL);
    memcpy(duplicate, s, length + 1);
    return (duplicate);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
    int length;

    for (length = 0; s[length] != 0; length++)
    {
    }
    return (length);
}

/**
 * compareChars - Compares characters of two strings.
 * @str: The input string.
 * @delim: The delimiter string.
 *
 * Return: 1 if the characters match, 0 if they do not.
 */
int compareChars(char str[], const char *delim)
{
    unsigned int i, j, k;

    for (i = 0, k = 0; str[i]; i++)
    {
        for (j = 0; delim[j]; j++)
        {
            if (str[i] == delim[j])
            {
                k++;
                break;
            }
        }
	}
    if (i == k)
        return (1);
    return (0);
}

/**
 * _strtok - Splits a string by a specified delimiter.
 * @str: The input string.
 * @delim: The delimiter.
 *
 * Return: The tokenized string.
 */
char *_strtok(char str[], const char *delim)
{
    static char *split = NULL, *end = NULL;
    char *start;
    unsigned int i, flag;

    if (str != NULL)
    {
        if (compareChars(str, delim))
            return (NULL);
	split = str;
	 i = _strlen(str);
        end = &str[i];
	 }
    start = split;
    if (start == end)
	     return (NULL);

    for (flag = 0; *split; split++)
    {
	     if (split != start)
            if (*split && *(split - 1) == '\0')
                break;
	     for (i = 0; delim[i]; i++)
        {
            if (*split == delim[i])
            {
                *split = '\0';
                if (split == start)
                    start++;
                break;
            }
        }
        if (flag == 0 && *split)
		       flag = 1;
    }
    if (flag == 0)
	      return (NULL);
    return (start);
}
/**
 * _isdigit - Determines if a string represents a number.
 *
 * @s: The input string.
 * Return: 1 if the string is a number, 0 otherwise.
 */
int _isdigit(const char *s)
{
    unsigned int i;

    for (i = 0; s[i]; i++)
    {
        if (s[i] < 48 || s[i] > 57)
            return (0);
    }
    return (1);
}

