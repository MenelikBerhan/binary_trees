#include "binary_trees.h"

/**
 * binary_tree_height - measures the height of a binary tree
 * @tree: a pointer to the root node of the tree to measure the height.
 *
 * Return: the height of binary tree or 0 if tree is NULL.
*/
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t h_left, h_right;

	if (!tree || (!tree->left && !tree->right))
		return (0);
	h_left = h_right = 0;
	if (tree->left)
		h_left = 1 + binary_tree_height(tree->left);
	if (tree->right)
		h_right = 1 + binary_tree_height(tree->right);

	return (h_left > h_right ? h_left : h_right);
}

/**
 * leaves_at_bottom - counts the leaves in a binary tree at last level
 * @tree: a pointer to the root node of the tree to count the number of leaves
 * @height: height of the tree
 *
 * Return: the number of leaves at last level in a binary tree
 * or 0 if tree is NULL
*/
size_t leaves_at_bottom(const binary_tree_t *tree, size_t height)
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

	return (leaves_at_bottom(tree->left, height)
		+ leaves_at_bottom(tree->right, height));
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

	height = binary_tree_height(*root);
	bottom_leaves = leaves_at_bottom(*root, height);
	temp = *root;
	for (i = 0; i < height; i++)
		temp = temp->left;
	for (j = 0, max_leaves = 1; j < height; j++)
		max_leaves *= 2;
	if (bottom_leaves == max_leaves)
		return (temp);

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
	if (temp->parent->left == temp)
		return (temp->parent);
	if (i % 4 != 0)
		return (temp->parent->parent->right);
	j_limit = i <= max_leaves / 2 ? i / 4 : (max_leaves - i) / 4;
	for (j = 0; j < j_limit + 2; j++)
		temp = temp->parent;
	temp = temp->right;
	for (j = 0; j < j_limit; j++)
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
	heap_t *node_parent, *prnt_lft, *prnt_right;

	while (new_node->parent && (new_node->n > new_node->parent->n))
	{
		node_parent = new_node->parent;
		prnt_lft = node_parent->left;
		prnt_right = node_parent->right;
		node_parent->left = new_node->left;
		node_parent->right = new_node->right;
		if (new_node->left)
			new_node->left->parent = node_parent;
		if (new_node->right)
			new_node->right->parent = node_parent;

		if (prnt_lft == new_node)
		{
			new_node->left = node_parent;
			new_node->right = prnt_right;
			if (prnt_right)
				prnt_right->parent = new_node;
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
