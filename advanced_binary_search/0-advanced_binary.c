#include "search_algos.h"
#include <stdio.h>

/**
 * _advanced_binary - Helper to perform advanced binary search recursively
 * @array: Pointer to the current subarray
 * @size: Size of the current subarray
 * @value: Value to search for
 *
 * Return: Pointer to first occurrence or NULL
 */
int *_advanced_binary(int *array, size_t size, int value)
{
	size_t i = 0;

	if (array == NULL || size == 0)
		return (NULL);

	printf("Searching in array: ");
	for (i = 0; i < size; i++)
	{
		printf("%d", array[i]);
		if (i < size - 1)
			printf(", ");
	}
	printf("\n");

	i = (size - 1) / 2;

	if (array[i] == value)
	{
		if (i == 0 || array[i - 1] != value)
			return (array + i);
		return (_advanced_binary(array, i + 1, value));
	}
	else if (array[i] > value)
	{
		return (_advanced_binary(array, i, value));
	}
	else
	{
		return (_advanced_binary(array + i + 1, size - i - 1, value));
	}
}

/**
 * advanced_binary - Performs advanced binary search for first occurrence
 * @array: Pointer to the full array
 * @size: Size of the array
 * @value: Value to search for
 *
 * Return: Index of the first occurrence or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	int *res = _advanced_binary(array, size, value);

	if (res == NULL)
		return (-1);
	return ((int)(res - array));
}
