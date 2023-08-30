#include "binary_trees.h"

/**
 * rotate_right - performs a right-rotation on a binary tree.
 * @node: a pointer to the node to rotate
 *
 * Return: a pointer to the new root node of the tree once rotated
 */
avl_t *rotate_righty(avl_t *node)
{
	avl_t *tmp = node->left;
	avl_t *tmp2 = tmp->right;

	tmp->right = node;
	node->left = tmp2;
	tmp->parent = node->parent;
	node->parent = tmp;
	if (tmp2)
		tmp2->parent = node;
	return (tmp);
}

/**
 * rotate_left - performs a left-rotation on a binary tree.
 * @node: a pointer to the node to rotate
 *
 * Return: a pointer to the new root node of the tree once rotated
 */
avl_t *rotate_lefty(avl_t *node)
{
	avl_t *tmp = node->right;
	avl_t *tmp2 = tmp->left;

	tmp->left = node;
	node->right = tmp2;
	tmp->parent = node->parent;
	node->parent = tmp;
	if (tmp2)
		tmp2->parent = node;
	return (tmp);
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
	if (!root)
		return (root);
	int bal = binary_tree_balance(root);

	if (bal > 1 && binary_tree_balance(root->left) >= 0)
		return (rotate_righty(root));
	if (bal > 1 && binary_tree_balance(root->left) < 0)
	{
		root->left = rotate_lefty(root->left);
		return (rotate_righty(root));
	}
	if (bal < -1 && binary_tree_balance(root->right) <= 0)
		return (rotate_lefty(root));
	if (bal < -1 && binary_tree_balance(root->right) > 0)
	{
		root->right = rotate_righty(root->right);
		return (rotate_lefty(root));
	}
	return (root);
}
