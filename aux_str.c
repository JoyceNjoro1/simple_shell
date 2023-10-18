#include "main.h"

/**
 * _strcat - Concatenate two strings.
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len;
	int src_len;

	for (dest_len = 0; dest[dest_len] != '\0'; dest_len++)
		;

	for (src_len = 0; src[src_len] != '\0'; src_len++)
	{
		dest[dest_len] = src[src_len];
		dest_len++;
	}

	dest[dest_len] = '\0';
	return dest;
}

/**
 * _strcpy - Copy the string pointed to by src.
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
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
 * @s1: String 1
 * @s2: String 2
 * Return: 0 if strings are equal, a positive value if s1 > s2, or a negative value if s1 < s2.
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
 * @s: Input string
 * @c: Character to locate
 * Return: Pointer to the first occurrence of the character c, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; s[i] != '\0'; i++)
		if (s[i] == c)
			return s + i;
	if (s[i] == c)
		return s + i;
	return NULL;
}

/**
 * _strspn - Get the length of a prefix substring.
 * @s: Input string
 * @accept: Accepted bytes
 * Return: Number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, match_found;

	for (i = 0; s[i] != '\0'; i++)
	{
		match_found = 1;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				match_found = 0;
				break;
			}
		}
		if (match_found == 1)
			break;
	}
	return i;
}

