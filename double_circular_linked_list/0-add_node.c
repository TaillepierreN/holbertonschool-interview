#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * create_node - Creates a new List node with a copy of the given string
 * @str: The string to duplicate into the new node
 * Return: Pointer to the newly created node, or NULL on failure
 */
static List *create_node(char *str)
{
	List *node = malloc(sizeof(List));

	if (!node)
		return (NULL);

	node->str = strdup(str);
	if (!node->str)
	{
		free(node);
		return (NULL);
	}

	node->next = node->prev = NULL;
	return (node);
}

/**
 * add_node_end - Adds a new node at the end of a double circular linked list
 * @list: Pointer to the list head pointer
 * @str: The string to duplicate into the new node
 * Return: Address of the new node, or NULL if fail
 */
List *add_node_end(List **list, char *str)
{
	List *node = create_node(str);

	if (!node)
		return (NULL);

	if (!*list)
	{
		node->next = node;
		node->prev = node;
		*list = node;
	}
	else
	{
		List *last = (*list)->prev;

		node->next = *list;
		node->prev = last;
		last->next = node;
		(*list)->prev = node;
	}

	return (node);
}

/**
 * add_node_begin - Adds a new node at the beginning of
 * a double circular linked list
 * @list: Pointer to the list head pointer
 * @str: The string to duplicate into the new node
 * Return: Address of the new node, or NULL if fail
 */
List *add_node_begin(List **list, char *str)
{
	List *node = add_node_end(list, str);

	if (node)
		*list = node;
	return (node);
}
