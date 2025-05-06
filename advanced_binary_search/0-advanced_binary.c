#include "search_algos.h"
#include <stdio.h>

/**
 * print_array - Prints the current subarray being searched
 * @array: Pointer to the first element
 * @start: Starting index
 * @end: Ending index
 */
void print_array(int *array, int start, int end)
{
	int i;

	printf("Searching in array: ");
	for (i = start; i <= end; i++)
	{
		printf("%d", array[i]);
		if (i < end)
			printf(", ");
	}
	printf("\n");
}

/**
 * recursive_search - Recursively searches for the first occurrence of value
 * @array: Pointer to the first element
 * @start: Start index
 * @end: End index
 * @value: Value to search for
 *
 * Return: Index of the first occurrence or -1
 */
int recursive_search(int *array, int start, int end, int value)
{
	int mid;

	if (start > end)
		return (-1);

	print_array(array, start, end);
	mid = start + (end - start) / 2;

	if (array[mid] == value)
	{
		if (mid == start || array[mid - 1] != value)
			return (mid);
		else
			return (recursive_search(array, start, mid, value));
	}
	else if (array[mid] < value)
	{
		return (recursive_search(array, mid + 1, end, value));
	}
	else
	{
		return (recursive_search(array, start, mid - 1, value));
	}
}

/**
 * advanced_binary - Calls recursive binary search to find first occurrence
 * @array: Sorted array
 * @size: Number of elements in array
 * @value: Value to search for
 *
 * Return: Index where value is located or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);

	return (recursive_search(array, 0, size - 1, value));
}