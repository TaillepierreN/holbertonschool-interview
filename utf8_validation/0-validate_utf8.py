#!/usr/bin/python3
"""
    Determines if a given data set represents a valid UTF-8 encoding.
"""


def validUTF8(data):
    """
    Determines how many bytes a character should have based on the first byte.
    Check that the following bytes start with 0b10.
    Returns True only if all bytes conform to UTF-8 encoding.
    """
    num_bytes = 0

    for num in data:
        byte = num & 0xFF

        if num_bytes == 0:
            if (byte >> 5) == 0b110:
                num_bytes = 1
            elif (byte >> 4) == 0b1110:
                num_bytes = 2
            elif (byte >> 3) == 0b11110:
                num_bytes = 3
            elif (byte >> 7):
                return False
        else:
            if (byte >> 6) != 0b10:
                return False
            num_bytes -= 1

    return num_bytes == 0
