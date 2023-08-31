#include "binary_trees.h"

/**
 * binary_tree_rotate_left - performs a left-rotation on a binary tree.
 * @tree: a pointer to the root node of the tree to rotate
 *
 * Return: a pointer to the new root node of the tree once rotated
 */
binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *new_root = tree->right;
	binary_tree_t *tmp = new_root->left;

	new_root->left = tree;
	tree->right = tmp;
	new_root->parent = tree->parent;
	tree->parent = new_root;
	if (tmp)
		tmp->parent = tree;
	return (new_root);
}
