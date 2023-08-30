#include "binary_trees.h"

/**
 * rotate_right - performs a right-rotation on a binary tree.
 * @node: a pointer to the node to rotate
 *
 * Return: a pointer to the new root node of the tree once rotated
 */
avl_t *rotate_right(avl_t *node)
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
avl_t *rotate_left(avl_t *node)
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
 * insert_node - Inserts a new node into an AVL tree.
 *
 * @tree: Pointer to the root node of the AVL tree.
 * @parent: Pointer to the parent node of the AVL tree.
 * @new: Pointer to the left or right child of the parent node.
 * @value: The value to store in the node to be inserted.
 *
 * Return: Pointer to the new root node of the AVL tree after insertion.
 *         NULL if tree is NULL.
 */
avl_t *insert_node(avl_t **tree, avl_t *parent, avl_t **new, int value)
{
	if (!(*tree))
	{
		*new = binary_tree_node(parent, value);
		return (*new);
	}

	if (value < (*tree)->n)
		(*tree)->left = insert_node(&((*tree)->left), *tree, new, value);
	else if (value > (*tree)->n)
		(*tree)->right = insert_node(&((*tree)->right), *tree, new, value);
	else
		return (*tree);
	int bal = binary_tree_balance(*tree);
	if (bal > 1 && value < (*tree)->left->n)
		*tree = rotate_right(*tree);
	else if (bal > 1 && value > (*tree)->left->n)
	{
		(*tree)->left = rotate_left((*tree)->left);
		*tree = rotate_right(*tree);
	}
	else if (bal < -1 && value > (*tree)->right->n)
		*tree = rotate_left(*tree);
	else if (bal < -1 && value < (*tree)->right->n)
	{
		(*tree)->right = rotate_right((*tree)->right);
		*tree = rotate_left(*tree);
	}
	return (*tree);
}

/**
 * avl_insert - Inserts a new node into an AVL tree.
 *
 * @tree: Pointer to the root node of the AVL tree to insert into.
 * @value: The value to store in the node to be inserted.
 *
 * Return: Pointer to the new node inserted into the AVL tree.
 *         NULL if tree is NULL or if the value already exists in the tree.
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node;

	if (!(*tree))
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}
	insert_node(tree, *tree, &new_node, value);
	return (new_node);
}
