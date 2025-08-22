#ifndef SUBSTRING_H
#define SUBSTRING_H
#include <stdlib.h>

/**
 * struct workspace_s - Working buffers and metadata for substring search
 * @string_length: length of input string s
 * @word_length: length of each word
 * @nb_words: number of words requested
 * @unique_count: number of unique words
 * @result_capacity: capacity for results array (string_length)
 * @workspace_buffer: single allocated slab for all arrays
 * @result: pointer to start indices written into workspace_buffer
 * @required_counts: required frequency of each unique word
 * @current_counts: current sliding-window frequencies
 * @word_to_unique: map words[i] -> unique index
 * @unique_words: array of pointers to unique words
 */
typedef struct workspace_s
{
	size_t string_length, word_length;
	int nb_words, unique_count, result_capacity;
	unsigned char *workspace_buffer;
	int *result, *required_counts, *current_counts, *word_to_unique;
	const char **unique_words;
} ws_t;

int *find_substring(char const *s, char const **words, int nb_words, int *n);

#endif
