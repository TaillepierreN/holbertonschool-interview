#include "search_algos.h"
#include <stdio.h>

/**
 * _advanced_binary - Recursive search for first occurrence
 * @array: Pointer to current subarray
 * @size: Size of current subarray
 * @value: Value to search for
 * Return: Pointer to found element or NULL
 */
int *_advanced_binary(int *array, size_t size, int value)
{
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	i = size / 2;

	if (array[i] == value)
	{
		if (i == 0 || array[i - 1] != value)
		{
			printf("Searching in array: ");
			for (size_t j = 0; j < size; j++)
				printf("%d%s", array[j], j == size - 1 ? "\n" : ", ");
			return (array + i);
		}

		printf("Searching in array: ");
		for (size_t j = 0; j <= i; j++)
			printf("%d%s", array[j], j == i ? "\n" : ", ");
		return (_advanced_binary(array, i, value));
	}
	else if (array[i] > value)
	{
		printf("Searching in array: ");
		for (size_t j = 0; j < i; j++)
			printf("%d%s", array[j], j == i - 1 ? "\n" : ", ");
		return (_advanced_binary(array, i, value));
	}
	else
	{
		printf("Searching in array: ");
		for (size_t j = i + 1; j < size; j++)
			printf("%d%s", array[j], j == size - 1 ? "\n" : ", ");
		return (_advanced_binary(array + i + 1, size - i - 1, value));
	}
}

/**
 * advanced_binary - Entry function to call recursive binary search
 * @array: Full array
 * @size: Full size
 * @value: Value to search
 * Return: Index of first match or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	int *res = _advanced_binary(array, size, value);

	if (res == NULL)
		return (-1);
	return (res - array);
}
