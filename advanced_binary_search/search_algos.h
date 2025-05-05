#ifndef SEARCH_ALGOS_H
#define SEARCH_ALGOS_H

#include <stddef.h>

int advanced_binary(int *array, size_t size, int value);
int recursive_search(int *array, size_t low, size_t high, int value);
void print_subarray(int *array, size_t low, size_t high);


#endif
