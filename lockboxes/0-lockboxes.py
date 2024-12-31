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
    # former method, added a more accurate one further down, with commentary
    """keychain = [0]
    for key in keychain:
        for looseKey in boxes[key]:
            if looseKey not in keychain and looseKey < len(boxes):
                keychain.append(looseKey)
    if len(boxes) == len(keychain):
        return True
    return False"""

    numberOfBoxes = len(boxes)

    # list to track if the boxes are opened or not
    openedBoxes = [False] * numberOfBoxes
    openedBoxes[0] = True

    # take the keys of the first box in a list
    keyring = list(set(boxes[0]))
    key_index = 0

    # iterate over the keys and open the boxes corresponding
    # adding the keys found into the keyring list
    while key_index < len(keyring):
        key = keyring[key_index]
        key_index += 1
        if 0 <= key < numberOfBoxes and not openedBoxes[key]:
            openedBoxes[key] = True
            keyring += boxes[key]

    return all(openedBoxes)
