#include "regex.h"

/* Return 1 if the first char of str matches the first
atom of pattern (a literal or '.') */
static int char_match(char s, char p)
{
	return ((p == '.') || (s == p));
}

/*
 * - '.' matches any single character
 * - 'x*' matches zero or more of 'x' (where x can also be '.')
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
