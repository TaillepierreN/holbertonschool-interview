#!/usr/bin/python3
"""
Module 0-island_perimeter
Defines a function to calculate the perimeter of an island in a grid
"""


def island_perimeter(grid):
    """
    Calculate the perimeter of the island described in grid.

    Parameters:
        grid (list of list of int): 2D map with 1 for land and 0 for water.

    Returns:
        int: perimeter of the island.
    """
    height = len(grid)
    width = len(grid[0]) if height > 0 else 0
    perimeter = 0

    for y in range(height):
        for x in range(width):
            if grid[y][x] == 1:
                # Start with 4 sides
                perimeter += 4

                # Subtract sides shared with land above
                if y > 0 and grid[y - 1][x] == 1:
                    perimeter -= 2

                # Subtract sides shared with land on the left
                if x > 0 and grid[y][x - 1] == 1:
                    perimeter -= 2

    return perimeter
