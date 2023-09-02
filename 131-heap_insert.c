#include "binary_trees.h"

/**
 * leaves_at_bottomi - counts the leaves in a binary tree at last level
 * @tree: a pointer to the root node of the tree to count the number of leaves
 * @height: height of the tree
 *
 * Return: the number of leaves at last level in a binary tree
 * or 0 if tree is NULL
*/
size_t leaves_at_bottomi(const binary_tree_t *tree, size_t height)
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

	return (leaves_at_bottomi(tree->left, height)
		+ leaves_at_bottomi(tree->right, height));
}

/**
 * find_insert_node - finds the left most parent in Max Binary Heap's lower
 * level to insert a new node and
 * @root: a double pointer to the root node of the Heap to insert the value
 *
 * Return: a pointer to the parent of the new node to be inserted
 */
heap_t *find_insert_node(heap_t **root)
{
	heap_t *temp;
	size_t bottom_leaves, height, i, j, j_limit, max_leaves;

	for (height = 0, temp = *root; temp && temp->left; height++)
		temp = temp->left;
	bottom_leaves = leaves_at_bottomi(*root, height);

	for (j = 0, max_leaves = 1; j < height; j++)
		max_leaves *= 2;
	if (bottom_leaves == max_leaves)
		return (temp);

	for (i = 1; i < bottom_leaves; i++)
	{
		if (i % 2 != 0)
			temp = temp->parent->right;
		else
		{
			j = i <= max_leaves / 2 ? i : max_leaves - i;
			for (j_limit = 1; j != 1 && j % 2 == 0; j /= 2)
				j_limit++;
			for (j = 0; j < j_limit; j++)
				temp = temp->parent;
			temp = temp->right;
			for (j = 0; j < j_limit - 1; j++)
				temp = temp->left;
		}
	}
	if (temp->parent->left == temp)
		return (temp->parent);

	j = i <= max_leaves / 2 ? i : max_leaves - i;
	for (j_limit = 1; j != 1 && j % 2 == 0; j /= 2)
		j_limit++;
	for (j = 0; j < j_limit; j++)
		temp = temp->parent;
	temp = temp->right;
	for (j = 0; j < j_limit - 2; j++)
		temp = temp->left;
	return (temp);
}

/**
 * heap_insert_helper - moves the newly inserted node up the tree if it
 * has an n field value greater than it's parent
 * @root: a double pointer to the root node of the Heap to insert the value
 * @new_node: a pointer to the newly inserted node
 *
 */
void heap_insert_helper(heap_t **root, heap_t *new_node)
{
	heap_t *node_parent, *prnt_lft, *prnt_rght;

	while (new_node->parent && (new_node->n > new_node->parent->n))
	{
		node_parent = new_node->parent;
		prnt_lft = node_parent->left;
		prnt_rght = node_parent->right;
		node_parent->left = new_node->left;
		node_parent->right = new_node->right;
		if (new_node->left)
			new_node->left->parent = node_parent;
		if (new_node->right)
			new_node->right->parent = node_parent;

		if (prnt_lft == new_node)
		{
			new_node->left = node_parent;
			new_node->right = prnt_rght;
			if (prnt_rght)
				prnt_rght->parent = new_node;
		}
		else
		{
			new_node->left = prnt_lft;
			new_node->right = node_parent;
			if (prnt_lft)
				prnt_lft->parent = new_node;
		}
		if (node_parent->parent)
		{
			if (node_parent->parent->left == node_parent)
				node_parent->parent->left = new_node;
			else
				node_parent->parent->right = new_node;
		}
		new_node->parent = node_parent->parent;
		node_parent->parent = new_node;
	}
	if (!new_node->parent)
		*root = new_node;
}

/**
 * heap_insert - inserts a value in Max Binary Heap
 * @root: a double pointer to the root node of the Heap to insert the value
 * @value: the value to store in the node to be inserted
 *
 * Return: a pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *node_parent;

	if (!root)
		return (NULL);
	if (!(*root))
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	new_node = binary_tree_node(NULL, value);
	node_parent = find_insert_node(root);
	new_node->parent = node_parent;

	if (node_parent->left)
		node_parent->right = new_node;
	else
		node_parent->left = new_node;

	heap_insert_helper(root, new_node);

	return (new_node);
}
