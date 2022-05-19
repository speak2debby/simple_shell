#include "simple_shell.h"

/**
 * insert_node_at_index - Inserts a new node at a given position
 * @head: Pointer to address of a list
 * @idx: Index of the list where new node should be added
 * @str: String
 *
 * Return: Address of the new node
 * Null if failed
 */
list_t *insert_node_at_index(list_t **head, unsigned int idx, char *str)
{
	unsigned int i;
	list_t *tmp;
	list_t *new;

	i = 0;
	tmp = *head;
	while (i < idx - 1)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	if (idx)
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	else
	{
		new->next = tmp;
		*head = new;
	}
	new->str = _strdup(str);
	return (new);
}
