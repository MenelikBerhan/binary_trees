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
 * leaves_at_bottom - counts the leaves in a binary tree at last level
 * @tree: a pointer to the root node of the tree to count the number of leaves
 * @height: height of the tree
 *
 * Return: the number of leaves in a binary tree or 0 if tree is NULL
*/
size_t leaves_at_bottom(const binary_tree_t *tree, size_t height)
{
	size_t depth = 0;
	binary_tree_t *temp = (binary_tree_t *) tree;

	if (!tree)
		return (0);

	while (temp->parent)
	{
		depth++;
		temp = temp->parent;
	}

	if (binary_tree_is_leaf(tree) && depth == height)
		return (1);

	return (leaves_at_bottom(tree->left, height)
		+ leaves_at_bottom(tree->right, height));
}

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * @tree: a pointer to the root node of the tree to check
 *
 * Return: 1 if tree is complete, or 0 if tree is not complete or is NULL
*/
int binary_tree_is_complete(const binary_tree_t *tree)
{
	binary_tree_t *tree_tmp = (binary_tree_t *) tree, *nxt_leaf;
	size_t height, leaves, nodes, size, i, j, j_limit, max_leaves;

	if (!tree_tmp)
		return (0);
	height = binary_tree_height(tree);
	size = binary_tree_size(tree);
	nodes = 1;
	for (i = binary_tree_height(tree) + 1; i > 0; i--)
		nodes *= 2;
	if (--nodes == size)
		return (1);
	leaves = leaves_at_bottom(tree, height);
	if (size - leaves != ((nodes + 1) / 2) - 1)
		return (0);
	for (i = 0; i < height - 1; i++)
		tree_tmp = tree_tmp->left;
	nxt_leaf = tree_tmp->left;
	if (!nxt_leaf)
		return (0);
	for (i = 1; i < leaves; i++)
	{
		if (i % 2 != 0)
			nxt_leaf = nxt_leaf->parent->right;
		else
		{
			for (j = 0, max_leaves = 1; j < height; j++)
				max_leaves *= 2;
			j_limit = i <= max_leaves / 2 ? i / 4 : (max_leaves - i) / 4;
			for (j = 0; j < j_limit + 2; j++)
				nxt_leaf = nxt_leaf->parent;
			nxt_leaf = nxt_leaf->right;
			for (j = 0; j < j_limit + 1; j++)
				nxt_leaf = nxt_leaf->left;
		}
		if (!nxt_leaf)
			return (0);
	}
	return (1);
}
