#ifndef REGEX_H
#define REGEX_H
/* regex.h */

/**
 * regex_match - Recursively match a string against a simple regex
 * @str: input string to scan (may be empty)
 * @pattern: pattern to match (may be empty); supports '.' and '*'
 *
 * Return: 1 if @pattern matches @str entirely, otherwise 0
 */
int regex_match(const char *str, const char *pattern);

#endif
