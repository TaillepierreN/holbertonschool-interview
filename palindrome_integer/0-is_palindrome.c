#include "palindrome.h"

int is_palindrome(unsigned long n)
{
	unsigned long original = n;
	unsigned long reversed = 0;

	while (n != 0)
	{
		reversed = reversed * 10 + (n % 10);
		n /= 10;
	}

	return (reversed == original) ? 1 : 0;
}
