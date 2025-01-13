#ifndef BINARY_TREES_H;
#define BINARY_TREES_H

#include <stddef.h>

/**
 * struct binary_trees_s - Binary tree node
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 */
struct binary_trees_s
{
	struct binary_trees_s *parent;
	struct binary_trees_s *left;
	struct binary_trees_s *right;
	int n;
};

typedef struct binary_trees_s binary_tree_t;
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value);


#endif /* BINARY_TREES_H */