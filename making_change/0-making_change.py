#!/usr/bin/python3
"""
determine the fewest number of coins needed to meet a given amount total
"""

def makeChange(coins, total):
	"""Determine the fewest number of coins needed to meet a given amount total.
	
	Args:
		coins (list): List of coin denominations.
		total (int): The total amount to make change for.
	"""
	if total <= 0:
		return 0
	coins.sort(reverse=True)
	coinCount = 0;

	for coin in coins:
		while total >= coin:
			total -= coin
			coinCount += 1
	return coinCount if total == 0 else -1
