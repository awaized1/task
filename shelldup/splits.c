#include "shell.h"

char **_strtok(char *line, char *delim);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

/**
 * token_len - Code locates delimiter index marking end
 *             of first token contained within string.
 * @str: String to be searched.
 * @delim: Delimiter character.
 *
 * Return: Delim index marking the end of
 *         intitial token pointed to be string.
 */

int token_len(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * count_tokens - Code counts the num of delimited
 *                words that is contained within a string.
 * @str: String to be searched.
 * @delim: Delimiter char.
 *
 * Return: Number of words contained in string
 */

int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Code tokenizes string.
 * @line: String.
 * @delim: Delimiter char to tokenize the string by.
 *
 * Return: Pointer to an array containing tokenized words.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));

	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
