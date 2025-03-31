#include "binary_trees.h"
#include <stdlib.h>


/**
 * sorted_array_to_avl - Converts a sorted array to an AVL tree
 * @array: The sorted array
 * @size: The size of the array
 *
 * Return: A pointer to the root of the AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (array == NULL || size == 0)
		return (NULL);
	
	return (build_avl(array, 0, (int)size - 1, NULL));
}


/**
 * build_avl - Recursively builds an AVL tree from a sorted array
 * @array: The sorted array
 * @start: The starting index of the subarray
 * @end: The ending index of the subarray
 * @parent: The parent node of the current node
 *
 * Return: A pointer to the root of the AVL tree, or NULL on failure
 */
avl_t *build_avl(int *array, int start, int end, avl_t *parent)
{
	avl_t *root;
	int mid = (start + end) / 2;

	if (start > end)
		return (NULL);
	
	root = create_node(parent, array[mid]);
	if (root == NULL)
		return (NULL);
	
	root->left = build_avl(array, start, mid - 1, root);
	root->right = build_avl(array, mid + 1, end, root);

	return (root);
}

/**
 * create_node - Creates a new AVL tree node
 * @parent: The parent node of the new node
 * @value: The value to store in the new node
 *
 * Return: A pointer to the new node, or NULL on failure
 */
avl_t *create_node(avl_t *parent, int value)
{
	avl_t *node = malloc(sizeof(avl_t));
	if (node == NULL)
		return (NULL);
	node->n = value;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	return (node);
}