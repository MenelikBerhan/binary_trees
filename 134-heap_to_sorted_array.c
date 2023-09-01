#include "binary_trees.h"

/**
 * binary_tree_is_leaf - checks if a node is a leaf.
 * @node: a pointer to the node to be checked
 *
 * Return: 1 if node is a leaf or 0 otherwise or if node is NULL.
*/
int binary_tree_is_leaf(const binary_tree_t *node)
{
	if (!node || node->left || node->right)
		return (0);
	return (1);
}

/**
 * binary_tree_size - measures the size (number of nodes) of a binary tree
 * @tree: a pointer to the root node of the tree to measure the size
 *
 * Return: the size of binary tree or 0 if tree is NULL.
*/
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	if (binary_tree_is_leaf(tree))
		return (1);

	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}


/**
 * heap_to_sorted_array - converts a Binary Max Heap to
 * a sorted array of integers
 * @heap: a pointer to the root node of the heap to convert
 * @size: an address to store the size of the array
 *
 * Return: the sorted array of integers
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
	size_t heap_size, i;
	int *sorted;

	if (!heap)
		return (NULL);
	heap_size = binary_tree_size(heap);
	*size = heap_size;
	sorted = malloc(sizeof(int) * heap_size);
	if (!sorted)
		return (NULL);
	for (i = 0; i < heap_size; i++)
	{
		sorted[i] = heap_extract(&heap);
	}
	return (sorted);
}
