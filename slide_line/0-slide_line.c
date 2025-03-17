#include "slide_line.h"
#include <stddef.h>

/**
 * slide_line - Slides and merges an array of integers to the left or right.
 * @line: The array of integers.
 * @size: The number of elements in the array.
 * @direction: The direction to slide (SLIDE_LEFT or SLIDE_RIGHT).
 *
 * Return: 1 on success, 0 on failure.
 */
int slide_line(int *line, size_t size, int direction)
{
    size_t i, j, last_merge;
    
    if (direction != SLIDE_LEFT && direction != SLIDE_RIGHT)
        return (0);
    
    if (direction == SLIDE_LEFT)
    {
        last_merge = 0;
        for (i = 0, j = 0; i < size; i++)
        {
            if (line[i] != 0)
            {
				// si j(endroit ou on va mettre le nombre)-1 est égale a position i
                if (j > 0 && line[j - 1] == line[i] && last_merge != j - 1)
                {
                    line[j - 1] *= 2;
                    line[i] = 0;
                    last_merge = j - 1;
                }
                else
                {
                    if (j != i)
                    {
                        line[j] = line[i];
                        line[i] = 0;
                    }
                    j++;
                }
            }
        }
    }
    else if (direction == SLIDE_RIGHT)
    {
        last_merge = size - 1;
        for (i = size, j = size; i > 0; i--)
        {
            if (line[i - 1] != 0)
            {
                if (j < size && line[j] == line[i - 1] && last_merge != j)
                {
                    line[j] *= 2;
                    line[i - 1] = 0;
                    last_merge = j;
                }
                else
                {
                    if (j != i)
                    {
                        line[j - 1] = line[i - 1];
                        line[i - 1] = 0;
                    }
                    j--;
                }
            }
        }
    }
    
    return (1);
}
