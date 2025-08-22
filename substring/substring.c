#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * token_to_index - Linear search a token among unique words
 * @token: pointer to token inside s
 * @unique_words: array of unique word pointers
 * @unique_count: number of unique words
 * @word_length: length of each word
 * Return: index in unique_words[], or -1 if not found
 **/
static int token_to_index(const char *token, const char **unique_words,
						  int unique_count, size_t word_length)
{
	for (int i = 0; i < unique_count; i++)
		if (strncmp(token, unique_words[i], word_length) == 0)
			return (i);
	return (-1);
}

/**
 * alloc_workspace - Allocate single slab and build unique-word tables
 * @ws: workspace (string_length and word_length must be set)
 * @words: array of words
 * @nb_words: number of words
 * Return: 0 on success, -1 on failure
 **/
static int alloc_workspace(ws_t *ws, const char **words, int nb_words)
{
	size_t ints_bytes = ((ws->result_capacity = (int)ws->string_length) + 3 * (size_t)nb_words) * sizeof(int);
	size_t ptrs_bytes = (size_t)nb_words * sizeof(const char *);
	int idx;

	ws->workspace_buffer = malloc(ints_bytes + ptrs_bytes);
	if (!ws->workspace_buffer)
		return (-1);

	ws->result = (int *)ws->workspace_buffer;
	ws->required_counts = ws->result + ws->result_capacity;
	ws->current_counts = ws->required_counts + nb_words;
	ws->word_to_unique = ws->current_counts + nb_words;
	ws->unique_words = (const char **)(ws->workspace_buffer + ints_bytes);
	ws->nb_words = nb_words;

	ws->unique_count = 0;
	for (int i = 0; i < nb_words; i++)
	{
		idx = -1;
		for (int j = 0; j < ws->unique_count; j++)
			if (strncmp(words[i], ws->unique_words[j], ws->word_length) == 0)
			{
				idx = j;
				break;
			}
		if (idx == -1)
		{
			ws->unique_words[ws->unique_count] = words[i];
			idx = ws->unique_count++;
		}
		ws->word_to_unique[i] = idx;
	}
	for (int i = 0; i < ws->unique_count; i++)
		ws->required_counts[i] = 0, ws->current_counts[i] = 0;
	for (int i = 0; i < nb_words; i++)
		ws->required_counts[ws->word_to_unique[i]]++;
	return (0);
}

/*
 * Small helper to clear counts
 * @arr: array to clear
 * @len: length of array
 */
static void zero_counts(int *arr, int len)
{
	for (int i = 0; i < len; i++)
		arr[i] = 0;
}

/**
 * slide_for_offset - Run the sliding window on one alignment offset
 * @s: input string
 * @ws: workspace
 * @offset: starting alignment in [0, word_length)
 * @found: in/out: number of indices already found
 * Return: void
 **/
static void slide_for_offset(const char *s, ws_t *ws, size_t offset, int *found)
{
	size_t left = offset, right = offset;
	int window_words = 0, idx, left_idx;

	zero_counts(ws->current_counts, ws->unique_count);

	while (right + ws->word_length <= ws->string_length)
	{
		idx = token_to_index(s + right, ws->unique_words,
							 ws->unique_count, ws->word_length);
		right += ws->word_length;

		if (idx == -1)
		{
			zero_counts(ws->current_counts, ws->unique_count);
			window_words = 0;
			left = right;
			continue;
		}

		ws->current_counts[idx]++;
		window_words++;

		while (ws->current_counts[idx] > ws->required_counts[idx])
		{
			left_idx = token_to_index(s + left, ws->unique_words,
									  ws->unique_count, ws->word_length);
			if (left_idx != -1)
			{
				ws->current_counts[left_idx]--;
				window_words--;
			}
			left += ws->word_length;
		}

		if (window_words == ws->nb_words)
		{
			ws->result[(*found)++] = (int)left;
			left_idx = token_to_index(s + left, ws->unique_words,
									  ws->unique_count, ws->word_length);
			if (left_idx != -1)
				ws->current_counts[left_idx]--;
			left += ws->word_length;
			window_words--;
		}
	}
}

/**
 * find_substring - Find starting indices where words concatenate exactly once
 * @s: string to scan
 * @words: array of words (same length)
 * @nb_words: number of words
 * @n: out param to store count of found indices
 * Return: malloc'ed array of indices (single slab) or NULL if none
 **/
int *find_substring(const char *s, const char **words, int nb_words, int *n)
{
	ws_t ws;
	int found = 0;
	size_t off;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return (NULL);
	ws.string_length = strlen(s);
	ws.word_length = strlen(words[0]);
	if (ws.string_length == 0 || ws.word_length == 0)
		return (NULL);
	for (int i = 1; i < nb_words; i++)
		if (strlen(words[i]) != ws.word_length)
			return (NULL);
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
