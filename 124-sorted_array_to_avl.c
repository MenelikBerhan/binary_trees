#include "binary_trees.h"

/**
 * to_avl_helper - wraps the sorted array conversion into an AVL tree
 * @arr: a pointer to the first element of the array to be converted
 * @start: the starting index of the subarray
 * @end: the ending index of the subarray
 *
 * Return: a pointer to the root node of the created AVL, or NULL on failure
 */
avl_t *to_avl_helper(int *arr, int start, int end)
{
	int mid;
	avl_t *root;

	if (start > end || !arr)
		return (NULL);
	mid = (start + end) / 2;
	root = binary_tree_node(NULL, arr[mid]);

	root->left = to_avl_helper(arr, start, mid - 1);
	root->right = to_avl_helper(arr, mid + 1, end);
	if (root->left)
		root->left->parent = root;
	if (root->right)
		root->right->parent = root;
	return (root);
}

/**
 * sorted_array_to_avl - builds an AVL tree from an array.
 * @array: a pointer to the first element of the array to be converted
 * @size: the number of element in the array
 *
 * Return: a pointer to the root node of the created AVL, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || !size)
		return (NULL);
	return (to_avl_helper(array, 0, size - 1));
}
