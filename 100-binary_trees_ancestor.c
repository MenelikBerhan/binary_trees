#include "binary_trees.h"

/**
 * binary_tree_depth - measures the depth of a node in a binary tree
 * @tree: a pointer to the node to measure the depth
 *
 * Return: the depth of node from root or 0 if tree is NULL.
*/
size_t binary_tree_depth(const binary_tree_t *tree)
{
	size_t depth = 0;

	if (!tree)
		return (0);
	while (tree->parent)
	{
		depth++;
		tree = tree->parent;
	}

	return (depth);
}

/**
 * binary_trees_ancestor - finds the lowest common ancestor of two nodes
 * @first: a pointer to the first node
 * @second: a pointer to the second node
 *
 * Return: a pointer to the lowest common ancestor node of the two given nodes,
 * or NULL if no common ancestor was found
*/
binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
					const binary_tree_t *second)
{
	/*
	 * no specific info given when both nodes are identical.
	 * as it is, this function returns the node itself.
	 */
	binary_tree_t *first_tmp = (binary_tree_t *) first,
		*second_tmp = (binary_tree_t *) second;
	size_t depth_first, depth_second;
	int i;

	depth_first = binary_tree_depth(first_tmp);
	depth_second = binary_tree_depth(second_tmp);

	for (i = depth_first - depth_second; i > 0; i--)
		first_tmp = first_tmp->parent;
	for (i = depth_second - depth_first; i > 0; i--)
		second_tmp = second_tmp->parent;

	while (first_tmp && second_tmp)
	{
		if (first_tmp == second_tmp)
			return (first_tmp);
		first_tmp = first_tmp->parent;
		second_tmp = second_tmp->parent;
	}
	return (NULL);
}
