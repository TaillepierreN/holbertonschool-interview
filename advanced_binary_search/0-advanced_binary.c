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
	if (low >= high)
		return;

	printf("Searching in array: ");

	if (low == high) {
		printf("%u\n", array[high]);
		return;
	}

	while (low <= high) {
		printf("%u", array[low]);
		if (low != high)
			printf(", ");
		low++;
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
	int mid = low + (high - low) / 2;

	print_array(array, high, low);

	if (array[mid] == value) {
		print_array(array, mid, low);
		if (array[mid] == array[mid - 1]) {
			print_array(array, mid, mid - 1);
			mid--;
		}
		return mid;
	}

	if (high >= low) {
		if (array[mid] > value)
			return binary_search(array, mid, low, value);
		else
			return binary_search(array, high, mid + 1, value);
	}

	return -1;
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
	int ret;

	if (!array)
		return -1;

	ret = binary_search(array, (int)size - 1, 0, value);
	return ret;
}