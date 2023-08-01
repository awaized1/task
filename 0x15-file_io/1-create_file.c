#include "main.h"

/**
 * create_file - This program creates a file.
 * @text_content: The pointer to a string to write.
 * @filename: A pointer to a name of the file to create.
 *
 * Return: If function fails - -1.
 *         Otherwise - 1.
 */
int create_file(const char *filename, char *text_content)
{
	int fa, w, len = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
			len++;
	}

	fa = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	w = write(fa, text_content, len);

	if (fa == -1 || w == -1)
		return (-1);

	close(fa);

	return (1);
}
