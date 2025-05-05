#include "search_algos.h"
#include <stdio.h>

/**
 * print_subarray - Prints the current subarray being searched
 * @array: Pointer to the first element of the array
 * @low: Starting index
 * @high: Ending index
 */
void print_subarray(int *array, size_t low, size_t high)
{
	size_t i;

	printf("Searching in array: ");
	for (i = low; i <= high; i++)
	{
		printf("%d", array[i]);
		if (i < high)
			printf(", ");
	}
	printf("\n");
}

/**
 * recursive_search - Recursively searches for the first occurrence of a value
 * @array: Pointer to the first element
 * @low: Starting index
 * @high: Ending index
 * @value: Value to search for
 * Return: Index of the first occurrence or -1
 */
int recursive_search(int *array, size_t low, size_t high, int value)
{
	size_t mid;

	if (low > high)
		return (-1);

	print_subarray(array, low, high);

	mid = low + (high - low) / 2;

	if (array[mid] == value)
	{
		if (mid == low || array[mid - 1] != value)
			return ((int)mid);
		return (recursive_search(array, low, mid, value));
	}
	else if (array[mid] > value)
		return (recursive_search(array, low, mid - 1, value));
	else
		return (recursive_search(array, mid + 1, high, value));
}

/**
 * advanced_binary - Calls recursive search to find first occurrence of value
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 * @value: Value to search for
 * Return: Index of first occurrence or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);
	return (recursive_search(array, 0, size - 1, value));
}
