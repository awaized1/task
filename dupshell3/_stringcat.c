#include "shell.h"

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strlen(const char *s);
char *_strcopy(char *dest, const char *src);

/**
 * _strlen - Code returns length of a string.
 * @s: Pointer to char string.
 *
 * Return: Len of the char string.
 */

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;

	return (len);
}

/**
 * _strcopy - Code copies string pointed by src, including the
 *           terminating null byte, to buff pointed by dest.
 * @dest: The pointer to destination of copied str.
 * @src: The pointer to the src of the source str.
 *
 * Return: The pointer to dest.
 */

char *_strcopy(char *dest, const char *src)
{
	size_t ab;

	for (ab = 0; src[ab] != '\0'; ab++)
		dest[ab] = src[ab];
	dest[ab] = '\0';
	return (dest);
}

/**
 * _strcat - Code concantenates two strings.
 * @dest: Pointer to the destination str.
 * @src: Pointer to the source str.
 *
 * Return: The pointer to dest string.
 */

char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';

	return (dest);
}

/**
 * _strncat - Code concantenates two strings where n number
 *            of bytes are copied from source.
 * @n: number of bytes to copy from src.
 * @dest: A Pointer to dest string.
 * @src: Pointer to source str.
 *
 * Return: The pointer to dest string.
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
