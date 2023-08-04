#include "shell.h"

char **_getenv(const char *var);
char **_copyenviron(void);
void free_env(void);

/**
 * _copyenviron - Code creates a copy of env.
 *
 * Return: If err occurs - NULL.
 *         Otherwise - Double pointer to new copy.
 */

char **_copyenviron(void)
{
	char **new_environ;
	size_t area;
	int index;

	for (area = 0; environ[area]; area++)
		;

	new_environ = malloc(sizeof(char *) * (area + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcopy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - Code frees the environment's copy.
 */

void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);

	free(environ);
}

/**
 * _getenv - Code gets an env variable from PATH.
 * @var: The name of env variable to get.
 *
 * Return: If the env variable doesn't exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */

char **_getenv(const char *var)
{
	int index, length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
