#include "binary_trees.h"

/**
 * binary_tree_is_leaf - checks if a node is a leaf.
 * @node: a pointer to the node to be checked
 *
 * Return: 1 if node is a leaf or 0 otherwise or if node is NULL.
*/
int binary_tree_is_leaf(const binary_tree_t *node)
{
	if (!node || node->left || node->right)
		return (0);
	return (1);
}
