#include "shell.h"

int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/**
 * _strchr - Code locates a char in a string.
 * @s: The str to be searched.
 * @c: The char to locate.
 *
 * Return: If c is found - pointer to first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *s, char c)
{
	int ind;

	for (ind = 0; s[ind]; ind++)
	{
		if (s[ind] == c)
			return (s + ind);
	}
	return (NULL);
}

/**
 * _strspn - Code gets length of a prefix substring.
 * @s: The string to search.
 * @accept: Prefix to measure.
 *
 * Return: The num of bytes in s which
 *         consist only of bytes from accept.
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - Code compares two strings.
 * @s1: The first string to compare.
 * @s2: Second string to compare.
 *
 * Return: A positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         A negative byte difference if s1 < s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - Code compare two strings.
 * @s2: Pointer to str.
 * @s1: Pointer to string.
 * @n: The first n bytes of str to compare.
 *
 * Return: Less than 0 if s1 shorter than s2
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 longer than s2.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
