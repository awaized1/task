#include "shell.h"

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Code prints current environment.
 * @front: Double pointer to the start of arguments
 * @args: Array of args passed to shell.
 *
 * Return: If an err occurs - -1.
 *   Otherwise - 0.
 *
 * Description: Code prints one variable per line in
 *              format 'variable'='value'.
 */

int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int num;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (num = 0; environ[num]; num++)
	{
		write(STDOUT_FILENO, environ[num], _strlen(environ[num]));
		write(STDOUT_FILENO, &nc, 1);
	}
	(void)args;
	return (0);
}

/**
 * shellby_setenv - Code changes or adds an env variable to PATH
 * @args: Array of arguments passed to shell
 * @front: Double pointer to the start of arguments
 *
 * Description: args[1] is the name of new or existing PATH va
 *              args[2] is the value to set the new or changed var to
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcopy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Code deletes an env variable from PATH.
 * @front: Double pointer to the start of arguments.
 * @args: Array of args passed to shell.
 * Description: args[1] is the PATH var to remove.
 *
 * Return: If an err occurs - -1.
 *         Otherwise - 0.
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int num, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (num = 0, index2 = 0; environ[num]; num++)
	{
		if (*env_var == environ[num])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[num];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;
	return (0);
}
