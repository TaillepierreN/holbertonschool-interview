#include "search_algos.h"
#include <stdio.h>

/**
 * print_array - prints the current array being searched
 * @array: the full array
 * @low: lower bound
 * @high: upper bound
 */
void print_array(int *array, size_t low, size_t high)
{
	size_t i;

	printf("Searching in array: ");
	for (i = low; i <= high; i++)
	{
		printf("%d", array[i]);
		if (i != high)
			printf(", ");
	}
	printf("\n");
}

/**
 * b_search - recursively searches for the first occurrence of value
 * @array: sorted array
 * @low: start index
 * @high: end index
 * @value: value to search
 * Return: index or -1
 */
int binary_search(int *array, size_t low, size_t high, int value)
{
	size_t mid;

	if (low > high)
		return (-1);

	print_array(array, low, high);
	mid = low + (high - low) / 2;

	if (array[mid] == value)
	{
		if (mid == low || array[mid - 1] != value)
			return (mid);
		return (binary_search(array, low, mid, value));
	}
	else if (array[mid] > value)
		return (binary_search(array, low, mid - 1, value));
	else
		return (binary_search(array, mid + 1, high, value));
}

/**
 * advanced_binary - performs advanced binary search
 * @array: sorted array
 * @size: number of elements
 * @value: value to search for
 * Return: index of first occurrence or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);
	return (binary_search(array, 0, size - 1, value));
}
