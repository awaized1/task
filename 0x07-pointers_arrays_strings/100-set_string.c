#include "main.h"

/**
 * set_string - sets the value of a pointer to a character
 * @s: a pointer to another pointer
 * @to: pointer char
 */

void set_string(char **s, char *to)
{
	*s = to;
}
