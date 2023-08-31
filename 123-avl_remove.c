#include "binary_trees.h"

/**
 * avl_remove_helper - removes a node from an AVL tree.
 * @root: a pointer to the root node of the tree where you will remove a node
 *
 * Return: a pointer to the new root node of the tree after removing the value
 */
avl_t *avl_remove_helper(avl_t *root)
{
	int bal;

	if (!root)
		return (root);
	bal = binary_tree_balance(root);

	if (bal > 1 && binary_tree_balance(root->left) >= 0)
		return (binary_tree_rotate_right(root));
	if (bal > 1 && binary_tree_balance(root->left) < 0)
	{
		root->left = binary_tree_rotate_left(root->left);
		return (binary_tree_rotate_right(root));
	}
	if (bal < -1 && binary_tree_balance(root->right) <= 0)
		return (binary_tree_rotate_left(root));
	if (bal < -1 && binary_tree_balance(root->right) > 0)
	{
		root->right = binary_tree_rotate_right(root->right);
		return (binary_tree_rotate_left(root));
	}
	return (root);
}

/**
 * avl_remove - removes a node from an AVL tree.
 * @root: a pointer to the root node of the tree where you will remove a node
 * @value: the value to remove in the tree
 *
 * Return: a pointer to the new root node of the tree after removing the value
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *tmp = NULL;

	if (!root)
		return (root);
	if (value < root->n)
		root->left = avl_remove(root->left, value);
	else if (value > root->n)
		root->right = avl_remove(root->right, value);
	else
	{
		if (!root->left || !root->right)
		{
			tmp = root->left ? root->left : root->right;
			if (!tmp)
			{
				tmp = root;
				root = NULL;
			}
			else
				*root = *tmp;
			free(tmp);
		}
		else
		{
			tmp = root->right;
			while (tmp->left)
				tmp = tmp->left;
			root->n = tmp->n;
			root->right = avl_remove(root->right, tmp->n);
		}
	}

	return (avl_remove_helper(root));
}
