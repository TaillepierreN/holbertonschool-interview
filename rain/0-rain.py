#!/usr/bin/python3
"""

Provides a function to compute the amount of water retained
after it rains, given a list of wall heights.
"""


def rain(walls):
    """
    Calculate the amount of rainwater retained between walls.
    """
    if not walls or len(walls) < 3:
        return 0

    total_water = 0
    left = 0
    right = len(walls) - 1
    left_max = 0
    right_max = 0

    while left < right:
        if walls[left] < walls[right]:
            if walls[left] >= left_max:
                left_max = walls[left]
            else:
                total_water += left_max - walls[left]
            left += 1
        else:
            if walls[right] >= right_max:
                right_max = walls[right]
            else:
                total_water += right_max - walls[right]
            right -= 1

    return total_water
