#include "main.h"
#include <string.h>

/**
 * _strcat - Concat 2 str.
 * @dest: Dest str
 * @src: Src str
 * Return: ptr to the dest str
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
 * _strcpy - Copy string
 * @dest: Dest string
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
 * _strcmp - Compare str
 * @s1: Str 1
 * @s2: Str 2
 * Return: 0 if strings are equal
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
 * _strchr - Locate a char in a str
 * @s: Input str
 * @c: Character to locate
 * Return: Pointer to th 1st occrence of the character c
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
 * _strspn - Get the length
 * @s: Input str
 * @accept: Accep bytes
 * Return: Number of accd bytes.
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
