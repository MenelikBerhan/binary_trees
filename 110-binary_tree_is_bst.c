#include "binary_trees.h"

/**
 * is_bst_util - checks if a binary tree is a valid BST.
 * @node: a pointer to the current node
 * @min: min allowed value
 * @max: max allowed value
 *
 * Return: 1 if the subtree is a valid BST, and 0 otherwise
 */
int is_bst_util(const binary_tree_t *node, int min, int max)
{
	if (!node)
		return (1);
	if (node->n <= min || node->n >= max)
		return (0);
	return (is_bst_util(node->left, min, node->n) &&
			is_bst_util(node->right, node->n, max));
}

/**
 * binary_tree_is_bst - checks if a binary tree is a valid Binary Search Tree.
 * @tree: a pointer to the root node
 *
 * Return: 1 if tree is a valid BST, and 0 otherwise
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (is_bst_util(tree, INT_MIN, INT_MAX));
}
