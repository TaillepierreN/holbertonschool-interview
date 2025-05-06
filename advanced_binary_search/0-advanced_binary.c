#include "search_algos.h"
#include <stdio.h>

/*
 * print_array - print values in array between low and high
 * @array: pointer to sorted array
 * @high: upper bound index
 * @low: lower bound index
 */
void print_array(int *array, size_t high, size_t low)
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

/*
 * binary_search - recursive binary search helper
 * @array: pointer to sorted array
 * @high: upper index
 * @low: lower index
 * @value: target value
 *
 * Return: index of first occurrence or -1 if not found
 */
int binary_search(int *array, size_t high, size_t low, int value)
{
	size_t mid;

	if (low > high)
		return (-1);

	print_array(array, high, low);
	mid = low + (high - low) / 2;

	if (array[mid] == value)
	{
		if (mid == low || array[mid - 1] != value)
			return ((int)mid);
		return (binary_search(array, mid, low, value));
	}
	else if (array[mid] < value)
	{
		return (binary_search(array, high, mid + 1, value));
	}
	else
	{
		if (mid == 0) // to prevent underflow
			return (-1);
		return (binary_search(array, mid - 1, low, value));
	}
}

/*
 * advanced_binary - binary search interface
 * @array: pointer to sorted array
 * @size: size of array
 * @value: value to search for
 *
 * Return: index of first occurrence or -1 if not found
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (!array || size == 0)
		return (-1);

	return (binary_search(array, size - 1, 0, value));
}
