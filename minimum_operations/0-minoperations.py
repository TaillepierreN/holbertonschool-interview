def minOperations(n):
    """
    Calculates the fewest number of operations needed to result in exactly n char
    using Copy All and Paste operations.
    
    Start with the smallest factor (2) and repeatedly divide by it and count it
    until it is no longer divisible.
    Add the factor to the operations for each division.
    Move onto the next factor and repeat the process until n is 1.

    :param n: Target number of characters
    :return: Minimum number of operations or 0 if n is not achievable
    """
    if n <= 1:
        return 0

    operations = 0
    factor = 2

    while n > 1:
        while n % factor == 0:
            operations += factor
            n = n // factor
        factor += 1

    return operations