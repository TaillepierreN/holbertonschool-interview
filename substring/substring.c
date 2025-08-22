#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * linear search among unique words (all same length)
 * @tok: token to find
 * @uniq: array of unique words
 * @ucount: number of unique words
 * @wlen: length of each word
 * Return: index in uniq[] or -1 if not found
 */
static int token_to_idx(const char *tok, const char **uniq,
						int ucount, size_t wlen)
{
	for (int i = 0; i < ucount; i++)
		if (strncmp(tok, uniq[i], wlen) == 0)
			return i;
	return -1;
}

/**
 * find_substring - Finds all starting indices of substring(s) in s
 * that is a concatenation of each word in words exactly once and without
 * any intervening characters.
 * @param s: The string to search within
 * @param words: Array of words to concatenate
 * @param nb_words: Number of words in the array
 * @param n: Pointer to an integer to store the number of results found
 * Return: Array of starting indices (malloc'ed) or NULL if none found
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
	size_t len_s, wlen;
	int unique = 0, found = 0;

	*n = 0;
	if (!s || !words || nb_words <= 0)
		return NULL;

	len_s = strlen(s);
	wlen = strlen(words[0]);
	if (wlen == 0 || len_s == 0)
		return NULL;

	for (int i = 1; i < nb_words; i++)
		if (strlen(words[i]) != wlen)
			return NULL;

	if (len_s < (size_t)nb_words * wlen)
		return NULL;

	size_t cap = len_s;
	size_t sz_ints = (cap + 3 * (size_t)nb_words) * sizeof(int);
	size_t sz_ptrs = (size_t)nb_words * sizeof(const char *);
	unsigned char *buf = malloc(sz_ints + sz_ptrs);
	if (!buf)
		return NULL;

	int *result = (int *)(buf);
	int *counts = result + cap;
	int *seen = counts + nb_words;
	int *word_to_unique = seen + nb_words;
	const char **uniq = (const char **)(buf + sz_ints);

	unique = 0;
	for (int i = 0; i < nb_words; i++)
	{
		int idx = -1;
		for (int j = 0; j < unique; j++)
			if (strncmp(words[i], uniq[j], wlen) == 0)
			{
				idx = j;
				break;
			}

		if (idx == -1)
		{
			idx = unique++;
			uniq[idx] = words[i];
		}
		word_to_unique[i] = idx;
	}

	for (int i = 0; i < unique; i++)
		counts[i] = 0;
	for (int i = 0; i < unique; i++)
		seen[i] = 0;

	for (int i = 0; i < nb_words; i++)
		counts[word_to_unique[i]]++;

	/* sliding window par offset in [0, wlen) */
	for (size_t offset = 0; offset < wlen; offset++)
	{
		size_t left = offset, right = offset;
		int window_words = 0;

		/* reset those we seen */
		for (int i = 0; i < unique; i++)
			seen[i] = 0;

		while (right + wlen <= len_s)
		{
			const char *tok = s + right;
			int idx = token_to_idx(tok, uniq, unique, wlen);
			right += wlen;

			if (idx == -1)
			{
				/* reset window on invalid token */
				for (int i = 0; i < unique; i++)
					seen[i] = 0;
				window_words = 0;
				left = right;
				continue;
			}

			seen[idx]++;
			window_words++;

			/* if word exceeds required count, we shrink from left */
			while (seen[idx] > counts[idx])
			{
				int lidx = token_to_idx(s + left, uniq, unique, wlen);
				if (lidx != -1)
				{
					seen[lidx]--;
					window_words--;
				}
				left += wlen;
			}

			/* full window (nb_words tokens) -> record */
			if (window_words == nb_words)
			{
				result[found++] = (int)left;

				/* move window forward by one word */
				{
					int lidx = token_to_idx(s + left, uniq, unique, wlen);
					if (lidx != -1)
						seen[lidx]--;
					left += wlen;
					window_words--;
				}
			}
		}
	}

	if (found == 0)
	{
		free(buf);
		return NULL;
	}

	*n = found;
	return result;
}
