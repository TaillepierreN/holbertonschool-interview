#include "regex.h"
/* regex.c */


/**
 * char_match - Check if one character matches a pattern atom
 * @s: the character from the input string
 * @p: the pattern atom (a literal or '.')
 *
 * Return: 1 if @p is '.' or equals @s, otherwise 0
 */
static int char_match(char s, char p)
{
	return ((p == '.') || (s == p));
}

/**
 * regex_match - Recursively match a string against a simple regex
 * @str: input string to scan (may be empty)
 * @pattern: pattern to match (may be empty); supports '.' and '*'
 *
 * Description:
 * The matcher supports two metacharacters:
 * '.' matches any single character.
 * 'x*' matches zero or more occurrences of the preceding atom 'x'
 * (where 'x' can be a literal or '.').
 *
 * Return: 1 if @pattern matches @str entirely, otherwise 0
 */
int regex_match(const char *str, const char *pattern)
{
	if (!pattern || *pattern == '\0')
		return ((str && *str == '\0') ? 1 : 0);

	if (*(pattern + 1) == '*')
	{
		if (*pattern == '*')
			return (0);

		if (regex_match(str, pattern + 2))
			return (1);

		while (str && *str != '\0' && char_match(*str, *pattern))
		{
			str++;
			if (regex_match(str, pattern + 2))
				return (1);
		}
		return (0);
	}

	if (str && *str != '\0' && char_match(*str, *pattern))
		return (regex_match(str + 1, pattern + 1));

	return (0);
}
