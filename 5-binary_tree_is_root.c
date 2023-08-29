#include "binary_trees.h"

/**
 * binary_tree_is_root - checks if a node is a root.
 * @node: a pointer to the node to be checked
 *
 * Return: 1 if node is a root or 0 otherwise or if node is NULL.
*/
int binary_tree_is_root(const binary_tree_t *node)
{
	if (!node || node->parent)
		return (0);
	return (1);
}
