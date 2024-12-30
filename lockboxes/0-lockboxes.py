#!/usr/bin/python3
"""
You have n number of locked boxes in front of you. 
Each box is numbered sequentially from 0 to n - 1 
and each box may contain keys to the other boxes.
"""

def canUnlockAll(boxes):
	"""
	A method that determines if all the boxes can be opened.

	Args:
		boxes (list of lists): contains list of boxes containing keys
	Return (bool):
		True if all boxes can be opened, else return False
	"""
	keychain = [0]
	for key in keychain:
		for looseKey in boxes[key]:
			if looseKey not in keychain and looseKey < len(boxes):
				keychain.append(looseKey)
	if len(boxes) == len(keychain):
		return True
	return False
