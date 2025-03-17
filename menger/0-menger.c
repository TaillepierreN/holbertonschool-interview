#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * is_blank - Checks if a given position in the menger sponge is blank.
 * @row: The row index.
 * @col: The column index.
 *
 * Return: 1 if the position should be blank, 0 otherwise.
 */
int is_blank(int row, int col)
{
    while (row > 0 || col > 0)
    {
        if (row % 3 == 1 && col % 3 == 1)
            return 1;
        row /= 3;
        col /= 3;
    }
    return 0;
}

/**
 * menger - Draws a 2D menger sponge of a given level.
 * @level: The level of the sponge to draw.
 */
void menger(int level)
{
    int size, row, col;
    
    if (level < 0)
        return;
    
    size = pow(3, level);
    
    for (row = 0; row < size; row++)
    {
        for (col = 0; col < size; col++)
        {
            if (is_blank(row, col))
                putchar(' ');
            else
                putchar('#');
        }
        putchar('\n');
    }
}