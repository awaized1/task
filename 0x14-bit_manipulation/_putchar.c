#include "main.h"
#include <unistd.h>
/**
 * _putchar - The program writes char c to standard output.
 * @c: The char to print
 *
 * Return:  1 if success
 * if error, return -1.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
