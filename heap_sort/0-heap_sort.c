#include "sort.h"

/**
 * swap_ints - Swaps two integers.
 * @a: First integer.
 * @b: Second integer.
 */
void swap_ints(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * heapify - Maintains the heap property between nodes.
 * @array: The array to sort.
 * @size: Full size of the array (for print_array).
 * @n: Current size of the heap.
 * @i: Index of the root.
 */
void heapify(int *array, size_t size, size_t n, size_t i)
{
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;

	if (left < n && array[left] > array[largest])
		largest = left;
	if (right < n && array[right] > array[largest])
		largest = right;

	if (largest != i)
	{
		swap_ints(&array[i], &array[largest]);
		print_array(array, size);
		heapify(array, size, n, largest);
	}
}

/**
 * heap_sort - Sorts an array of integers in ascending order using Heap sort.
 * @array: Array to sort.
 * @size: Size of the array.
 */
void heap_sort(int *array, size_t size)
{
	size_t i;

	if (!array || size < 2)
		return;

	for (i = size / 2; i > 0; i--)
		heapify(array, size, size, i - 1);

	for (i = size; i > 1; i--)
	{
		swap_ints(&array[0], &array[i - 1]);
		print_array(array, size);
		heapify(array, size, i - 1, 0);
	}
}
