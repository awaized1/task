#include "shell.h"

void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_alias - This is a builtin command that prints all aliases
 * @args: The arrays of args.
 * @front: Double pointer to the start of arguments.
 *
 * Return: If error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int t, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (t = 0; args[t]; t++)
	{
		temp = aliases;
		value = _strchr(args[t], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[t], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + t, 1);
		}
		else
			set_alias(args[t], value);
	}

	return (ret);
}

/**
 * set_alias - Code will set an existing alias 'name' with a new value,
 * or creates new alias.
 * @value:The value of alias. 1st char is a '='.
 * @var_name: Name of new alias.
 */

void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Code prints the alias in new format name='value'.
 * @alias: The pointer to an alias.
 */

void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcopy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - Code goes through the args and replace matching alias
 * with their respective values.
 * @args: The pointer to args.
 *
 * Return: pointer to the arguments.
 */

char **replace_aliases(char **args)
{
	alias_t *temp;
	int a;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (a = 0; args[a]; a++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[a], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcopy(new_value, temp->value);
				free(args[a]);
				args[a] = new_value;
				a--;
				break;
			}
			temp = temp->next;
		}
	}
	return (args);
}
