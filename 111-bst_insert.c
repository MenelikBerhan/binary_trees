#include "binary_trees.h"

/**
 * bst_insert - inserts a value in a Binary Search Tree.
 * @tree: a pointer to the root node of the BST to insert the value
 * @value: the value to store in the node to be inserted
 *
 * Return: a pointer to the created node, or NULL on failure
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	bst_t *node = NULL, *parent = NULL;

	if (!tree)
		return (NULL);
	if (!*tree)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}
	node = *tree;
	while (node)
	{
		parent = node;
		if (value < node->n)
			node = node->left;
		else if (value > node->n)
			node = node->right;
		else
			return (NULL);
	}
	node = binary_tree_node(parent, value);
	if (value < parent->n)
		parent->left = node;
	else
		parent->right = node;
	return (node);
}
