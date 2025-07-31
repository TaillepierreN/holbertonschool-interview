#include "holberton.h"

/**
 * wildcmp - Compares two strings and returns 1 if they can be
 * considered identical. The second string can contain the special
 * character * which can replace any string (including an empty string).
 * @s1: The first string
 * @s2: The second string (can include wildcards)
 *
 * If both strings reach the end => return 1 (they match).
 * If s2 is '*':
 *    - Skip repeated '*'s.
 *    - Try matching 0 char (move s2) or 1+ chars (move s1).
 * If current characters match, move to next in both strings.
 * If none of the above match => return 0 (not identical).
 *
 * Return: 1 if strings can be considered identical, otherwise 0
 */
int wildcmp(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);

	if (*s2 == '*')
	{
		if (*(s2 + 1) == '*')
			return (wildcmp(s1, s2 + 1));

		if (wildcmp(s1, s2 + 1))
			return (1);
		if (*s1 != '\0' && wildcmp(s1 + 1, s2))
			return (1);
	}

	if (*s1 == *s2)
		return (wildcmp(s1 + 1, s2 + 1));

	return (0);
}
