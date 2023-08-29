#include "binary_trees.h"

/**
 * binary_tree_insert_right - creates and inserts a new node as
 * the right-child of a parent node.
 * @parent: pointer to parent node of the right node to be created
 * @value: value of the right node to be created
 *
 * Return: pointer to the newly created node or
 * NULL on failure or if parent is NULL.
*/
binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;

	if (!parent)
		return (NULL);
	new_node = malloc(sizeof(binary_tree_t));
	if (!new_node)
		return (NULL);
	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = parent->right;
	if (parent->right)
		(parent->right)->parent = new_node;
	parent->right = new_node;


	return (new_node);
}
