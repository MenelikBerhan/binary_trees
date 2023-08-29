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

/**
 * binary_tree_height - measures the height of a binary tree
 * @tree: a pointer to the root node of the tree to measure the height.
 *
 * Return: the height of binary tree or 0 if tree is NULL.
*/
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t h_left, h_right;

	if (!tree || binary_tree_is_leaf(tree))
		return (0);
	h_left = h_right = 0;
	if (tree->left)
		h_left = 1 + binary_tree_height(tree->left);
	if (tree->right)
		h_right = 1 + binary_tree_height(tree->right);

	return (h_left > h_right ? h_left : h_right);
}

/**
 * binary_tree_size - measures the size (number of nodes) of a binary tree
 * @tree: a pointer to the root node of the tree to measure the size
 *
 * Return: the size of binary tree or 0 if tree is NULL.
*/
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	if (binary_tree_is_leaf(tree))
		return (1);

	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * binary_tree_is_perfect - checks if a binary tree is perfect
 * @tree: a pointer to the root node of the tree to check
 *
 * Return: 1 if tree is perfect, or 0 otherwise or if tree is NULL
*/
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	size_t total_nodes;
	int i;
	/**
	 * is a single node w/o children a perfect tree?
	 * this function assume it to be so.
	*/
	if (!tree)
		return (0);
	total_nodes = 1;
	for (i = binary_tree_height(tree) + 1; i > 0; i--)
		total_nodes *= 2;
	total_nodes--;
	return (binary_tree_size(tree) == total_nodes);
}
