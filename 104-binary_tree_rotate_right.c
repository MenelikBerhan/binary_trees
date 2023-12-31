#include "binary_trees.h"

/**
 * binary_tree_rotate_right - performs a right-rotation on a binary tree.
 * @tree: a pointer to the root node of the tree to rotate
 *
 * Return: a pointer to the new root node of the tree once rotated
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *new_root;
	binary_tree_t *tmp;

	if (!tree)
		return (NULL);
	new_root = tree->left;
	tmp = new_root->right;
	new_root->right = tree;
	tree->left = tmp;
	new_root->parent = tree->parent;
	tree->parent = new_root;
	if (tmp)
		tmp->parent = tree;
	return (new_root);
}
