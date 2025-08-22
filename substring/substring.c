#include <stdlib.h>
#include <string.h>
#include "substring.h"

/* Helper macros to keep functions short (Betty-friendly) */
#define CLEAR_CURRENT_COUNTS(ws) \
	zero_counts((ws)->current_counts, (ws)->unique_count)

#define RESET_WINDOW() \
	do { \
		CLEAR_CURRENT_COUNTS(ws); \
		window_words = 0; \
		left = right; \
	} while (0)

#define SHRINK_LEFT_WINDOW() \
	do { \
		left_idx = token_to_index(s + left, ws->unique_words, \
					  ws->unique_count, ws->word_length); \
		if (left_idx != -1) { \
			ws->current_counts[left_idx]--; \
			window_words--; \
		} \
		left += ws->word_length; \
	} while (0)

#define RECORD_HIT() \
	do { \
		ws->result[(*found)++] = (int)left; \
		left_idx = token_to_index(s + left, ws->unique_words, \
					  ws->unique_count, ws->word_length); \
		if (left_idx != -1) \
			ws->current_counts[left_idx]--; \
		left += ws->word_length; \
		window_words--; \
	} while (0)

#define ASSIGN_WS_POINTERS() \
	do { \
		ws->result = (int *)ws->workspace_buffer; \
		ws->required_counts = ws->result + ws->result_capacity; \
		ws->current_counts = ws->required_counts + nb_words; \
		ws->word_to_unique = ws->current_counts + nb_words; \
		ws->unique_words = (const char **)( \
			ws->workspace_buffer + ints_bytes); \
	} while (0)

#define MAP_WORD_TO_UNIQUE() \
	do { \
		idx = -1; \
		for (j = 0; j < ws->unique_count; j++) { \
			if (strncmp(words[i], ws->unique_words[j], \
				    ws->word_length) == 0) { \
				idx = j; \
				break; \
			} \
		} \
		if (idx == -1) { \
			ws->unique_words[ws->unique_count] = words[i]; \
			idx = ws->unique_count++; \
		} \
		ws->word_to_unique[i] = idx; \
	} while (0)

/**
 * token_to_index - Linear search a token among unique words
 * @token: pointer to token inside s
 * @unique_words: array of unique word pointers
 * @unique_count: number of unique words
 * @word_length: fixed length of each word
 * Return: index in unique_words[], or -1 if not found
 **/
static int token_to_index(const char *token, const char **unique_words,
			  int unique_count, size_t word_length)
{
	int i;

	for (i = 0; i < unique_count; i++)
	{
		if (strncmp(token, unique_words[i], word_length) == 0)
			return (i);
	}
	return (-1);
}

/**
 * zero_counts - Fill an int array with zeros
 * @array: array to clear
 * @length: number of elements
 **/
static void zero_counts(int *array, int length)
{
	int i;

	for (i = 0; i < length; i++)
		array[i] = 0;
}

/**
 * alloc_workspace - Single slab alloc and build unique-word tables
 * @ws: workspace (string_length and word_length must be set)
 * @words: array of words
 * @nb_words: number of words
 * Return: 0 on success, -1 on failure
 **/
static int alloc_workspace(ws_t *ws, const char **words, int nb_words)
{
	size_t ints_bytes, ptrs_bytes;
	int i, j, idx;

	ws->result_capacity = (int)ws->string_length;
	ints_bytes = (ws->result_capacity + 3 * (size_t)nb_words) *
		     sizeof(int);
	ptrs_bytes = (size_t)nb_words * sizeof(const char *);
	ws->workspace_buffer = malloc(ints_bytes + ptrs_bytes);
	if (!ws->workspace_buffer)
		return (-1);

	ASSIGN_WS_POINTERS();
	ws->nb_words = nb_words;

	ws->unique_count = 0;
	for (i = 0; i < nb_words; i++)
		MAP_WORD_TO_UNIQUE();

	zero_counts(ws->required_counts, ws->unique_count);
	zero_counts(ws->current_counts, ws->unique_count);
	for (i = 0; i < nb_words; i++)
		ws->required_counts[ws->word_to_unique[i]]++;

	return (0);
}

/**
 * slide_for_offset - Sliding window on alignment @offset
 * @s: input string
 * @ws: workspace
 * @offset: starting alignment in [0, word_length)
 * @found: in/out count of found indices
 **/
static void slide_for_offset(const char *s, ws_t *ws,
			     size_t offset, int *found)
{
	size_t left = offset, right = offset;
	int window_words = 0, idx, left_idx;

	CLEAR_CURRENT_COUNTS(ws);
	while (right + ws->word_length <= ws->string_length)
	{
		idx = token_to_index(s + right, ws->unique_words,
				     ws->unique_count, ws->word_length);
		right += ws->word_length;

		if (idx == -1)
		{
			RESET_WINDOW();
			continue;
		}
		ws->current_counts[idx]++;
		window_words++;

		while (ws->current_counts[idx] > ws->required_counts[idx])
			SHRINK_LEFT_WINDOW();

		if (window_words == ws->nb_words)
			RECORD_HIT();
	}
}

/**
 * find_substring - Find indices where words concatenate exactly once
 * @s: string to scan
 * @words: array of words (same length)
 * @nb_words: number of words
 * @n: out param to store count of found indices
 * Return: malloc'ed array of indices (single slab) or NULL if none
 **/
int *find_substring(const char *s, const char **words,
		    int nb_words, int *n)
{
	ws_t ws;
	int found = 0, i;
	size_t off;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return (NULL);

	ws.string_length = strlen(s);
	ws.word_length = strlen(words[0]);
	if (ws.string_length == 0 || ws.word_length == 0)
		return (NULL);

	for (i = 1; i < nb_words; i++)
	{
		if (strlen(words[i]) != ws.word_length)
			return (NULL);
	}
	if (ws.string_length < (size_t)nb_words * ws.word_length)
		return (NULL);

	if (alloc_workspace(&ws, words, nb_words) != 0)
		return (NULL);

	for (off = 0; off < ws.word_length; off++)
		slide_for_offset(s, &ws, off, &found);

	if (found == 0)
	{
		free(ws.workspace_buffer);
		return (NULL);
	}
	*n = found;
	return (ws.result);
}
