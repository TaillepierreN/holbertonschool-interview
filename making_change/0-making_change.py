#!/usr/bin/python3
"""
determine the fewest number of coins needed to meet a given amount total
"""


def makeChange(coins, total):
    """Determine the fewest number of coins
    needed to meet a given amount total.

    Args:
        coins (list): List of coin denominations.
        total (int): The total amount to make change for.
    """
    if total <= 0:
        return 0

    minAmount = [float('inf')] * (total + 1)
    minAmount[0] = 0

    for coin in coins:
        for i in range(coin, total + 1):
            minAmount[i] = min(minAmount[i], minAmount[i - coin] + 1)

    return minAmount[total] if minAmount[total] != float('inf') else -1
