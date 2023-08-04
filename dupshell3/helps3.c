#include "shell.h"

void variable_replacement(char **args, int *exe_ret);
void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);

/**
 * free_args - Code frees up mem taken by arguments.
 * @args: A terminated null pointer containing commands/arguments.
 * @front: Double pointer to the start of arguments.
 */

void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);
	free(front);
}

/**
 * get_pid - Code gets present process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              info about current process. The PID is the
 *              first word inside the file. The function reads the PID into
 *              a buffer and replaces space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL if failure.
 */

char *get_pid(void)
{
	size_t b = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);

	if (!buffer)
	{
		close(file);
		return (NULL);
	}

	read(file, buffer, 120);
	while (buffer[b] != ' ')
		b++;
	buffer[b] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Code gets the value corresponding to the env var
 * @len: Length of the env var to search for.
 * @beginning: The env var to search.
 *
 * Return: If var not found - an empty str.
 *         Otherwise - the value of the env var.
 *
 * Description: Variables are stored in format VARIABLE=VALUE.
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcopy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Code handles var replacement
 * @line: Double pointer that contains the command and arguments
 * @exe_ret: Pointer to the return val of the last executed command
 *
 * Description: Replaces $$ with the current PID, $? with return value
 *              of the last executed program, and env variables
 *              preceded by $ with their corresponding value.
 */

void variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
		    old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
					     old_line[k] != '$' &&
					     old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
