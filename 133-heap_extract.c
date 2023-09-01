#include "binary_trees.h"
#include <stdio.h>

/**
 * binary_tree_height1 - measures the height of a binary tree
 * @tree: a pointer to the root node of the tree to measure the height.
 *
 * Return: the height of binary tree or 0 if tree is NULL.
*/
size_t binary_tree_height1(const binary_tree_t *tree)
{
	size_t h_left, h_right;

	if (!tree || (!tree->left && !tree->right))
		return (0);
	h_left = h_right = 0;
	if (tree->left)
		h_left = 1 + binary_tree_height1(tree->left);
	if (tree->right)
		h_right = 1 + binary_tree_height1(tree->right);

	return (h_left > h_right ? h_left : h_right);
}

/**
 * leaves_at_bottom1 - counts the leaves in a binary tree at last level
 * @tree: a pointer to the root node of the tree to count the number of leaves
 * @height: height of the tree
 *
 * Return: the number of leaves at last level in a binary tree
 * or 0 if tree is NULL
*/
size_t leaves_at_bottom1(const binary_tree_t *tree, size_t height)
{
	size_t depth = 0;
	binary_tree_t *temp = (binary_tree_t *) tree;

	if (!tree)
		return (0);

	while (temp->parent)
	{
		depth++;
		temp = temp->parent;
	}

	if ((!tree->left && !tree->right) && depth == height)
		return (1);

	return (leaves_at_bottom1(tree->left, height)
		+ leaves_at_bottom1(tree->right, height));
}

/**
 * find_last_node - finds last node on the last level in Max Binary Heap
 * @root: a double pointer to the root node of the Heap to insert the value
 *
 * Return: a pointer to last node on the last level to be moved to root
 */
heap_t *find_last_node(heap_t **root)
{
	heap_t *temp;
	size_t bottom_leaves, height, i, j, j_limit, max_leaves;

	height = binary_tree_height1(*root);
	bottom_leaves = leaves_at_bottom1(*root, height);
	temp = *root;
	for (i = 0; i < height; i++)
		temp = temp->left;
	for (j = 0, max_leaves = 1; j < height; j++)
		max_leaves *= 2;


	for (i = 1; i < bottom_leaves; i++)
	{
		if (i % 2 != 0)
			temp = temp->parent->right;
		else if (i % 4 == 0)
		{
			j_limit = i <= max_leaves / 2 ? i / 4 : (max_leaves - i) / 4;
			for (j = 0; j < j_limit + 2; j++)
				temp = temp->parent;
			temp = temp->right;
			for (j = 0; j < j_limit + 1; j++)
				temp = temp->left;
		}
		else
			temp = temp->parent->parent->right->left;
	}
	return (temp);
}

/**
 * heap_extract_helper - moves the last node set as a root downwards
 * @root: a double pointer to the root node of heap
 * @last_node: the last node set as root after extraction
 *
 * Return: the value stored in the root node
 */
void heap_extract_helper(heap_t **root, heap_t *last_node)
{
	heap_t *left, *right, *l_node, *r_node;
	int n_left, n_right;

	while (last_node->left || last_node->right)
	{
		if (((last_node->left && last_node->right) && ((last_node->left->n <= last_node->n) && (last_node->right->n <= last_node->n)))
		|| ((last_node->left && !last_node->right) && (last_node->left->n <= last_node->n)))
			break;
		l_node = last_node->left;
		r_node = last_node->right;
		n_left = last_node->left ? last_node->left->n : 0;
		n_right = last_node->right ? last_node->right->n : 0;
		if (n_left >= n_right)
		{
			left = last_node->left->left;
			right = last_node->left->right;
			last_node->left->right = last_node->right;
			if (last_node->right)
				last_node->right->parent = last_node->left;
			last_node->left->parent = last_node->parent;
			if (last_node->parent)
			{
				if (last_node->parent->left == last_node)
					last_node->parent->left = last_node->left;
				else
					last_node->parent->right = last_node->left;
			}
			else
				*root = last_node->left;
			last_node->right = right;
			last_node->left = left;
			if (right)
				right->parent = last_node;
			if (left)
				left->parent = last_node;
			l_node->left = last_node;
			last_node->parent = l_node;
		}
		else
		{
			left = last_node->right->left;
			right = last_node->right->right;
			last_node->right->left = last_node->left;
			if (last_node->left)
				last_node->left->parent = last_node->right;
			last_node->right->parent = last_node->parent;
			if (last_node->parent)
			{
				if (last_node->parent->left == last_node)
					last_node->parent->left = last_node->right;
				else
					last_node->parent->right = last_node->right;
			}
			else
				*root = last_node->right;
			last_node->right = right;
			last_node->left = left;
			if (right)
				right->parent = last_node;
			if (left)
				left->parent = last_node;
			r_node->right = last_node;
			last_node->parent = r_node;
		}
	}
}

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: a double pointer to the root node of heap
 *
 * Return: the value stored in the root node
 */
int heap_extract(heap_t **root)
{
	heap_t *last_node, *temp = NULL;
	int extracted;

	if (!root || !(*root))
		return (0);
	
	last_node = find_last_node(root);
	if (*root == last_node)
	{
		free(*root);
		return (0);
	}
	extracted = (*root)->n;
	if (last_node->parent == *root)
	{
		if ((*root)->left == last_node)
			last_node->right = (*root)->right;
		else
			last_node->left = (*root)->left;
		if (last_node->left)
			last_node->left->parent = last_node;
		if (last_node->right)
			last_node->right->parent = last_node;
	}
	else
	{
		if ((*root)->left)
		{
			last_node->left = (*root)->left;
			(*root)->left->parent = last_node;
		}
		if ((*root)->right)
		{
			last_node->right = (*root)->right;
			(*root)->right->parent = last_node;
		}
	}
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;
	last_node->parent = NULL;
	temp = *root;
	*root = last_node;
	free(temp);
	heap_extract_helper(root, last_node);
	return (extracted);
}
