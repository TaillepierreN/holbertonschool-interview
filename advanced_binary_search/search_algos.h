#ifndef SEARCH_ALGOS_H
#define SEARCH_ALGOS_H

#include <stddef.h>

int advanced_binary(int *array, size_t size, int value);
int recursive_search(int *array, int start, int end, int value);
void print_array(int *array, int start, int end);

#endif
