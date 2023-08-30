#include "binary_trees.h"

/**
 * bst_remove - removes a node from a Binary Search Tree.
 * @root: a pointer to the root node of the tree where you will remove a node
 * @value: the value to remove in the tree
 *
 * Return: a pointer to the new root node of the tree after removing the value
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *node = NULL, *parent = NULL, *tmp = NULL;

	if (!root)
		return (NULL);
	node = root;
	while (node)
	{
		if (value < node->n)
			node = node->left;
		else if (value > node->n)
			node = node->right;
		else
			break;
	}
	if (!node)
		return (root);
	if (node->left && node->right)
	{
		tmp = node->right;
		while (tmp->left)
			tmp = tmp->left;
		node->n = tmp->n;
		node = tmp;
	}
	if (node->left)
		tmp = node->left;
	else
		tmp = node->right;
	parent = node->parent;
	if (tmp)
		tmp->parent = parent;
	if (!parent)
		root = tmp;
	else if (parent->left == node)
		parent->left = tmp;
	else
		parent->right = tmp;
	free(node);
	return (root);
}
