#include "binary_trees.h"

/**
 * height - measures the height of a binary tree.
 * @tree: a pointer to the root node of the tree to measure the height.
 *
 * Return: height of the tree, and 0 otherwise.
 */
int height(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (0);
	left_height = height(tree->left);
	right_height = height(tree->right);

	if (left_height > right_height)
		return (left_height + 1);
	else
		return (right_height + 1);
}

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
	int diff;

	if (!node)
		return (1);
	if (node->n <= min || node->n >= max)
		return (0);
	diff = abs(height(node->left) - height(node->right));
	if (diff > 1)
		return (0);
	return (is_bst_util(node->left, min, node->n) &&
			is_bst_util(node->right, node->n, max));
}

/**
 * binary_tree_is_avl - checks if a binary tree is a valid AVL Tree.
 * @tree: a pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid AVL Tree, and 0 otherwise.
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (is_bst_util(tree, INT_MIN, INT_MAX));
}
