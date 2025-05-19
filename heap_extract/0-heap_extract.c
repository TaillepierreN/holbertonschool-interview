#include "binary_trees.h"
#include <stdlib.h>

/**
 * get_tree_height - Measure the height of a binary tree.
 * @tree: Pointer to root node.
 * Return: Heightn0 if tree is NULL.
 */
static size_t get_tree_height(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	size_t left = get_tree_height(tree->left);
	size_t right = get_tree_height(tree->right);

	return ((left > right ? left : right) + 1);
}

/**
 * get_last_node - Finds the last node.
 * @root: Pointer to root node.
 * @height: Height of the heap.
 * Return: Pointer to last node.
 */
static heap_t *get_last_node(heap_t *root, size_t height)
{
	if (!root || height == 0)
		return (NULL);
	if (height == 1)
		return (root);

	heap_t *right = get_last_node(root->right, height - 1);

	if (right)
		return (right);
	return get_last_node(root->left, height - 1);
}

/**
 * heapify_down - Rebuilds heap property by pushing down.
 * @root: Pointer to root node.
 */
static void heapify_down(heap_t *root)
{
	heap_t *max = root;

	while (max)
	{
		heap_t *largest = max;

		if (max->left && max->left->n > largest->n)
			largest = max->left;
		if (max->right && max->right->n > largest->n)
			largest = max->right;

		if (largest == max)
			break;

		int tmp = max->n;
		max->n = largest->n;
		largest->n = tmp;
		max = largest;
	}
}

/**
 * heap_extract - Extracts the root from a max binary heap.
 * @root: pointer to root node.
 * Return: Value of extracted node, 0 on failure.
 */
int heap_extract(heap_t **root)
{
	if (!root || !*root)
		return (0);

	int value = (*root)->n;

	if (!(*root)->left && !(*root)->right)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	size_t height = get_tree_height(*root);
	heap_t *last = get_last_node(*root, height);

	if (!last)
		return (0);

	(*root)->n = last->n;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;
	free(last);

	heapify_down(*root);
	return (value);
}
