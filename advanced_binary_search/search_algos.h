#ifndef SEARCH_ALGOS_H
#define SEARCH_ALGOS_H

#include <stddef.h>

int advanced_binary(int *array, size_t size, int value);
int binary_search(int *array, size_t high, size_t low, int value);
void print_array(int *array, size_t high, size_t low);

#endif
