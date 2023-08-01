#include "lists.h"

/**
 * pop_listint - The program deletes the head node
 * @head: A pointer to the first element
 *
 * Return: the data in the elements that were deleted,
 * or 0 if list is empty
 */
int pop_listint(listint_t **head)
{
	listint_t *temp;
	int numb;

	if (!head || !*head)
		return (0);

	numb = (*head)->n;
	temp = (*head)->next;
	free(*head);
	*head = temp;

	return (numb);
}
