#include "binary_trees.h"

/**
 * binary_tree_insert_left - creates and inserts a new node as
 * the left-child of a parent node.
 * @parent: pointer to parent node of the left node to be created
 * @value: value of the left node to be created
 *
 * Return: pointer to the newly created node or
 * NULL on failure or if parent is NULL.
*/
binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;

	if (!parent)
		return (NULL);
	new_node = malloc(sizeof(binary_tree_t));
	if (!new_node)
		return (NULL);
	new_node->n = value;
	new_node->parent = parent;
	new_node->right = NULL;
	new_node->left = parent->left;
	if (parent->left)
		(parent->left)->parent = new_node;
	parent->left = new_node;

	return (new_node);
}
