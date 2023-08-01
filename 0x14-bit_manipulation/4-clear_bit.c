#include "main.h"

/**
 * clear_bit - Program sets the bit to 0
 * @n: a pointer to number to change
 * @index: index of the bit
 *
 * Return: 1 if success, -1 if failure.
 */

int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = (~(1UL << index) & *n);
	return (1);
}
