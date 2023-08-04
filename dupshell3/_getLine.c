#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

/**
 * _realloc - Code rallocates memory block using malloc and free.
 * @old_size: Size in bytes of allocated space to pointer.
 * @ptr: Pointer to memory previously allocated.
 * @new_size: Size for new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - Pointer to reallocated mem block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);

	return (mem);
}

/**
 * assign_lineptr - Code reassigns linepointer variable for _getline.
 * @b: Size of buffer.
 * @lineptr: Buffer to store a string.
 * @n: Size of linepointer.
 * @buffer: String to assign to linepointer.
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcopy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Code reads input from stream.
 * @lineptr: Buffer to save the input.
 * @n: Size of linepointer.
 * @stream: Stream to be read.
 *
 * Return: Number of bytes read.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int a;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		a = read(STDIN_FILENO, &c, 1);
		if (a == -1 || (a == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (a != 0)
		input = 0;

	return (ret);
}
