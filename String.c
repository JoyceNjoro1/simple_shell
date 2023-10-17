#include "main.h"

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len;
	int src_len;

	for (dest_len = 0; dest[dest_len] != '\0'; dest_len++);
	for (src_len = 0; src[src_len] != '\0'; src_len++)
	{
		dest[dest_len] = src[src_len];
		dest_len++;
	}

	dest[dest_len] = '\0';
	return dest;
}

/**
 * _strcpy - Copy a string from source to destination.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src);
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;
}

/**
 * _strcmp - Compare two strings.
 *
 * @s1: First string to compare.
 * @s2: Second string to compare.
 *
 * Return:
 * - 0 if the strings are equal.
 * - Positive value if s1 is greater than s2.
 * - Negative value if s1 is less than s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i;
	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return 1;
	if (s1[i] < s2[i])
		return -1;
	return 0;
}

/**
 * _strchr - Locate a character in a string.
 *
 * @s: String to search.
 * @c: Character to find.
 *
 * Return: Pointer to the first occurrence of the character c in s.
 *         Returns NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);

	if (*(s + i) == c)
		return (s + i);

	return NULL;
}

/**
 * _strspn - Get the length of a prefix substring.
 *
 * @s: Initial segment.
 * @accept: Set of accepted characters.
 *
 * Return: Number of accepted characters at the beginning of s.
 */
int _strspn(char *s, char *accept)
{
	int i, j, found;

	for (i = 0; s[i] != '\0'; i++)
	{
		found = 0;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
			break;
	}

	return i;
}

