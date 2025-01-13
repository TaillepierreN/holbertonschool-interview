#include <stdlib.h>
#include "binary_trees.h"

/**
 * heapify_up - Restores the Max Heap property by moving the node upwards
 * @node: Pointer to the inserted node
 * Return: Pointer to the node after heapify
 */
heap_t *max_heap_move(heap_t *node)
{
	int temp;

	while (node->parent && node->n > node->parent->n)
	{
		temp = node->n;
		node->n = node->parent->n;
		node->parent->n = temp;
		node = node->parent;
	}
	return (node);
}

/**
 * insert_node - Finds the proper place to insert a new node in level order
 * @root: Pointer to the root node
 * @value: Value to store in the new node
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *insert_node(heap_t *root, int value)
{
	heap_t *new_node;
	heap_t *queue[1024];
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		heap_t *current = queue[front++];

		if (!current->left)
		{
			new_node = binary_tree_node(current, value);
			current->left = new_node;
			return (new_node);
		}
		else
			queue[rear++] = current->left;

		if (!current->right)
		{
			new_node = binary_tree_node(current, value);
			current->right = new_node;
			return (new_node);
		}
		else
			queue[rear++] = current->right;
	}
	return (NULL);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to insert in the new node
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node;

	if (!root)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	new_node = insert_node(*root, value);
	if (!new_node)
		return (NULL);

	return (max_heap_move(new_node));
}
