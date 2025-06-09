#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * merge - Merges two subarrays into the original array in sorted order
 * @array: Original array to sort into
 * @buffer: Temporary buffer to assist merging
 * @left: Starting index of left subarray
 * @mid: Ending index of left subarray
 * @right: Ending index of right subarray
 */
void merge(int *array, int *buffer, size_t left, size_t mid, size_t right)
{
	size_t i, j, k;

	printf("Merging...\n[left]: ");
	print_array(array + left, mid - left);
	printf("[right]: ");
	print_array(array + mid, right - mid);

	i = left;
	j = mid;
	k = left;

	while (i < mid && j < right)
	{
		if (array[i] < array[j])
			buffer[k++] = array[i++];
		else
			buffer[k++] = array[j++];
	}
	while (i < mid)
		buffer[k++] = array[i++];
	while (j < right)
		buffer[k++] = array[j++];

	for (i = left; i < right; i++)
		array[i] = buffer[i];

	printf("[Done]: ");
	print_array(array + left, right - left);
}

/**
 * merge_sort_recursive - Recursively sorts array using merge sort
 * @array: The array to sort
 * @buffer: Temporary buffer to assist merging
 * @left: Starting index
 * @right: Ending index
 */
void merge_sort_recursive(int *array, int *buffer, size_t left, size_t right)
{
	size_t mid;

	if (right - left < 2)
		return;

	mid = left + (right - left) / 2;
	merge_sort_recursive(array, buffer, left, mid);
	merge_sort_recursive(array, buffer, mid, right);
	merge(array, buffer, left, mid, right);
}

/**
 * merge_sort - Sorts an array using merge sort algorithm
 * @array: The array to be sorted
 * @size: Number of elements
 */
void merge_sort(int *array, size_t size)
{
	int *buffer;

	if (!array || size < 2)
		return;

	buffer = malloc(sizeof(int) * size);
	if (!buffer)
		return;

	merge_sort_recursive(array, buffer, 0, size);
	free(buffer);
}
