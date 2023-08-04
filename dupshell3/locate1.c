#include "shell.h"

list_t *get_path_dir(char *path);
char *fill_path_dir(char *path);

/**
 * get_location - Code locates cmd in PATH.
 * @command: Command to locate.
 *
 * Return: If error occurs or command cannot be located - NULL.
 *         Otherwise - full pathname of command.
 */

char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcopy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);
		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - Code copies path and also replaces /sandwiched/trailing
 *   /leading colons with the current working dir.
 * @path: Colon-separated list of dir.
 *
 * Return: Copy of path with any sandwiched/trailing/leading colons replaced
 *   with the current working dir.
 */

char *fill_path_dir(char *path)
{
	int i, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';

	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Code tokenizes colon-separated list of
 *                dir into a list_s linked list.
 * @path: A colon-separated list of dir.
 *
 * Return: The pointer to initialized linked list.
 */

list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);

	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
