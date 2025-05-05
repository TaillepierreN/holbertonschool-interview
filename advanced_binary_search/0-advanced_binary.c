#include "search_algos.h"
#include <stdio.h>

/*
 * print_array - prints array from low to high index
 * @array: pointer to sorted array of ints
 * @high: upper bound index
 * @low: lower bound index
 */
static void print_array(int *array, size_t high, size_t low)
{
	size_t i;

	if (low > high)
		return;

	printf("Searching in array: ");
	for (i = low; i <= high; i++) {
		printf("%d", array[i]);
		if (i < high)
			printf(", ");
	}
	printf("\n");
}

/*
 * binary_search - recursive binary search helper
 * @array: pointer to sorted array
 * @high: upper index bound
 * @low: lower index bound
 * @value: target value to search for
 *
 * Return: index of first occurrence of value, or -1 if not found
 */
static int binary_search(int *array, size_t high, size_t low, int value)
{
	size_t mid;

	if (low > high)
		return -1;

	print_array(array, high, low);

	mid = low + (high - low) / 2;

	if (array[mid] == value) {
		if (mid > low && array[mid - 1] == value)
			return binary_search(array, mid - 1, low, value);
		return mid;
	}

	if (array[mid] > value)
		return binary_search(array, mid - 1, low, value);
	else
		return binary_search(array, high, mid + 1, value);
}

/*
 * advanced_binary - searches for value using binary search
 * @array: pointer to sorted array of ints
 * @size: total size of array
 * @value: value to find
 *
 * Return: index of first occurrence, or -1 if not found
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (!array || size == 0)
		return -1;

	return binary_search(array, size - 1, 0, value);
}
