#include "main.h"

/**
 * get_bit - Program returns the bit value at an index to a decimal
 * @n:The num to search through
 * @index: an index
 *
 * Return: value
 */

int get_bit(unsigned long int n, unsigned int index)
{
	int bit_val;

	if (index > 63)
		return (-1);

	bit_val = (n >> index) & 1;

	return (bit_val);
}
