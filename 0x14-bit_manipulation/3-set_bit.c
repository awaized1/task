#include "main.h"

/**
 * set_bit - Program sets a bit at an index to 1
 * @n: a pointer to the num to change
 * @index: index of 1
 *
 * Return: 1 if successful, -1 on failure
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	if (index >= sizeof(n) * 8)
		return (-1);

	return (!!(*n |= 1L << index));
}
