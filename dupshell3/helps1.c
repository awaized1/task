#include "shell.h"

int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
char *get_a(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);

/**
 * get_a - Code gets a command from stdin.
 * @line: Buffer to store command.
 * @exe_ret: The return value of most recent executed command.
 *
 * Return: If error occurs - NULL.
 *         Otherwise - the pointer to stored command.
 */

char *get_a(char *line, int *exe_ret)
{
	size_t b = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &b, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_a(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle(&line, read);

	return (line);
}

/**
 * call_args - Code to partition the operators from commands and calls them
 * @front: Double pointer to the start of arguments.
 * @args: Array of args.
 * @exe_ret: Return val of parent process' last executed command.
 *
 * Return: Return value of last executed cmd.
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);

	return (ret);
}

/**
 * run_args - Code calls the execution of cmd.
 * @args: Array of args
 * @front: Double pointer to the start of arguments.
 * @exe_ret: Return value of parent process' last executed command.
 *
 * Return: Return value of most recently executed command.
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int ret, a;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (a = 0; args[a]; a++)
		free(args[a]);

	return (ret);
}

/**
 * handle_args - Code gets, calls, and executes a command
 * @exe_ret: Return value of the parent process' recently executed command
 *
 * Return: If eof is read - END_OF_FILE (-2).
 *         If input cannot be tokenized - -1.
 *         Otherwise - The exit value of the recently executed command.
 */

int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_a(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - Code checks if there are leading ';', ';;', '&&', or '||'.
 * @args: Pointer to tokenized commands and args
 *
 * Return: If a ';', '&&', or '||' is placed in an invalid position - 2.
 *   Otherwise - 0.
 */

int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
