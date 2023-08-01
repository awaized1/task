#include <stdio.h>
#include "main.h"

/**
 * main - Program prints the number of arguments passed to the program
 * @argc: a number of arguments
 * @argv: a array of arguments
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
(void) argv; /*Ignore argv*/
	printf("%d\n", argc - 1);

	return (0);
}
