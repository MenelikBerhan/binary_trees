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
 * binary_tree_depth - measures the depth of a node in a binary tree
 * @tree: a pointer to the node to measure the depth
 *
 * Return: the depth of node from root or 0 if tree is NULL.
*/
size_t binary_tree_depth(const binary_tree_t *tree)
{
	size_t depth = 0;

	if (!tree)
		return (0);
	while (tree->parent)
	{
		depth++;
		tree = tree->parent;
	}

	return (depth);
}

/**
 * level_order_helper - goes through a binary tree using pre-order traversal.
 * @tree: a pointer to the root node of the tree to traverse
 * @func: a pointer to a function to call for each node. The value in the
 * node will be passed as a parameter to this function.
 * @depth: depth of nodes to call func for
 *
 * If tree or func is NULL, does nothing.
*/
void level_order_helper(const binary_tree_t *tree, void (*func)(int),
							size_t depth)
{
	if (!tree || !func)
		return;
	if (binary_tree_depth(tree) == depth)
		func(tree->n);
	level_order_helper(tree->left, func, depth);
	level_order_helper(tree->right, func, depth);
}

/**
 * binary_tree_levelorder - goes through a binary tree
 * using level-order traversal.
 * @tree: a pointer to the root node of the tree to traverse
 * @func: a pointer to a function to call for each node. The value in the
 * node will be passed as a parameter to this function.
 *
 * If tree or func is NULL, does nothing.
*/
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	size_t depth, height;
	/* const binary_tree_t *temp = tree, *nxt_start; */

	if (!tree || !func)
		return;

	height = binary_tree_height(tree);
	for (depth = 0; depth <= height; depth++)
	{
		level_order_helper(tree, func, depth);
	}
}
