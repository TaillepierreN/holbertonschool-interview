#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list
 * @list: Pointer to the head of the skip list
 * @value: Value to search for
 *
 * Return: Pointer to the first node where value is located,
 * or NULL if not found
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *node, *jump;

	if (list == NULL)
		return (NULL);

	node = list;
	jump = list->express;

	while (jump && jump->n < value)
	{
		printf("Value checked at index [%lu] = [%d]\n", jump->index, jump->n);
		node = jump;
		jump = jump->express;
	}

	if (jump)
		printf("Value checked at index [%lu] = [%d]\n", jump->index, jump->n);

	print_found_range(node, jump);

	while (node && node != jump)
	{
		printf("Value checked at index [%lu] = [%d]\n", node->index, node->n);
		if (node->n == value)
			return (node);
		node = node->next;
	}

	if (jump && jump->n == value)
		return (jump);

	return (NULL);
}

/**
 * print_found_range - Prints the range of indices where the value was found
 * @start: Pointer to the start node of the range
 * @end: Pointer to the end node of the range
 *
 * Return: void
 */
void print_found_range(skiplist_t *start, skiplist_t *end)
{
	if (!start)
		return;

	if (!end)
	{
		end = start;
		while (end->next)
			end = end->next;
	}

	printf("Value found between indexes [%lu] and [%lu]\n",
		   start->index, end->index);
}
