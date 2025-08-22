#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * struct workspace_s - Working buffers and metadata
 * @len_s: length of input string s
 * @wlen: length of each word
 * @nb_words: number of words requested
 * @unique: number of unique words
 * @cap: capacity for results array (len_s)
 * @buf: single allocated slab
 * @result: pointer to start indices written into @buf
 * @counts: required frequency of each unique word
 * @seen: current sliding-window frequencies
 * @word_to_unique: map words[i] -> unique index
 * @uniq: array of pointers to unique words
 */
typedef struct workspace_s
{
	size_t len_s, wlen;
	int nb_words, unique, cap;
	unsigned char *buf;
	int *result, *counts, *seen, *word_to_unique;
	const char **uniq;
} ws_t;

/**
 * token_to_idx - Linear search a token among unique words (fixed length)
 * @tok: token pointer inside s
 * @uniq: array of unique word pointers
 * @ucount: number of unique words
 * @wlen: word length
 * Return: index in uniq[], or -1 if not found
 **/
static int token_to_idx(const char *tok, const char **uniq,
						int ucount, size_t wlen)
{
	int i;

	for (i = 0; i < ucount; i++)
		if (strncmp(tok, uniq[i], wlen) == 0)
			return (i);
	return (-1);
}

/**
 * validate_inputs - Validate arguments and derive sizes
 * @s: input string
 * @words: array of words
 * @nb_words: number of words
 * @len_s: out param: length of s
 * @wlen: out param: length of a word
 * Return: 0 on success, -1 on failure
 **/
static int validate_inputs(char const *s, char const **words, int nb_words,
						   size_t *len_s, size_t *wlen)
{
	int i;

	if (!s || !words || nb_words <= 0)
		return (-1);
	*len_s = strlen(s);
	*wlen = strlen(words[0]);
	if (*len_s == 0 || *wlen == 0)
		return (-1);
	for (i = 1; i < nb_words; i++)
		if (strlen(words[i]) != *wlen)
			return (-1);
	if (*len_s < (size_t)nb_words * (*wlen))
		return (-1);
	return (0);
}

/**
 * alloc_workspace - Allocate single slab and build unique-word tables
 * @ws: workspace (len_s and wlen must be set)
 * @s: input string (unused, kept for symmetry)
 * @words: array of words
 * @nb_words: number of words
 * Return: 0 on success, -1 on failure
 **/
static int alloc_workspace(ws_t *ws, char const *s,
						   char const **words, int nb_words)
{
	size_t sz_ints, sz_ptrs;
	int i, j, idx;

	(void)s;
	ws->nb_words = nb_words;
	ws->cap = (int)ws->len_s;
	sz_ints = (ws->cap + 3 * (size_t)nb_words) * sizeof(int);
	sz_ptrs = (size_t)nb_words * sizeof(const char *);
	ws->buf = malloc(sz_ints + sz_ptrs);
	if (!ws->buf)
		return (-1);

	ws->result = (int *)ws->buf;
	ws->counts = ws->result + ws->cap;
	ws->seen = ws->counts + nb_words;
	ws->word_to_unique = ws->seen + nb_words;
	ws->uniq = (const char **)(ws->buf + sz_ints);

	ws->unique = 0;
	for (i = 0; i < nb_words; i++)
	{
		idx = -1;
		for (j = 0; j < ws->unique; j++)
			if (strncmp(words[i], ws->uniq[j], ws->wlen) == 0)
			{
				idx = j;
				break;
			}
		if (idx == -1)
			ws->uniq[ws->unique++] = words[i], idx = ws->unique - 1;
		ws->word_to_unique[i] = idx;
	}

	for (i = 0; i < ws->unique; i++)
		ws->counts[i] = 0, ws->seen[i] = 0;
	for (i = 0; i < nb_words; i++)
		ws->counts[ws->word_to_unique[i]]++;
	return (0);
}

/**
 * reset_seen - Zero the sliding-window counts
 * @ws: workspace
 * Return: void
 **/
static void reset_seen(ws_t *ws)
{
	int i;

	for (i = 0; i < ws->unique; i++)
		ws->seen[i] = 0;
}

/**
 * slide_for_offset - Run the sliding window on one alignment offset
 * @s: input string
 * @ws: workspace
 * @offset: starting alignment in [0, wlen)
 * @found: in/out: number of indices already found
 * Return: void
 **/
static void slide_for_offset(char const *s, ws_t *ws,
							 size_t offset, int *found)
{
	size_t left = offset, right = offset;
	int window_words = 0, idx, lidx;

	reset_seen(ws);
	while (right + ws->wlen <= ws->len_s)
	{
		idx = token_to_idx(s + right, ws->uniq, ws->unique, ws->wlen);
		right += ws->wlen;

		if (idx == -1)
		{
			reset_seen(ws);
			window_words = 0;
			left = right;
			continue;
		}
		ws->seen[idx]++;
		window_words++;

		while (ws->seen[idx] > ws->counts[idx])
		{
			lidx = token_to_idx(s + left, ws->uniq, ws->unique, ws->wlen);
			if (lidx != -1)
				ws->seen[lidx]--, window_words--;
			left += ws->wlen;
		}
		if (window_words == ws->nb_words)
		{
			ws->result[(*found)++] = (int)left;
			lidx = token_to_idx(s + left, ws->uniq, ws->unique, ws->wlen);
			if (lidx != -1)
				ws->seen[lidx]--;
			left += ws->wlen;
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
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	ws_t ws;
	int found = 0;
	size_t off;

	*n = 0;
	if (validate_inputs(s, words, nb_words, &ws.len_s, &ws.wlen) != 0)
		return (NULL);
	if (alloc_workspace(&ws, s, words, nb_words) != 0)
		return (NULL);

	for (off = 0; off < ws.wlen; off++)
		slide_for_offset(s, &ws, off, &found);

	if (found == 0)
	{
		free(ws.buf);
		return (NULL);
	}
	*n = found;
	return (ws.result);
}
