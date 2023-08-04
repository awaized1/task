#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Code creates err msg for permission denied failures.
 * @args: Array of args passed to the command.
 *
 * Return: Error string.
 */

char *error_126(char **args)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcopy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - Code creates an err msg for command not found failures.
 * @args: Array of args passed to command.
 *
 * Return: Error string.
 */

char *error_127(char **args)
{
	char *error, *hist_str;
	int leng;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	leng = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (leng + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcopy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);

	return (error);
}
