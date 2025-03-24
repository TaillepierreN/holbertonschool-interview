#!/usr/bin/python3
import sys


def is_safe(board, row, col):
    """
    check if placing a queen at a specified position is safe
    """
    # iterate over the rows, get the column of the queen
    # and check if it's the same column of if it's in the
    # same diagonal as the current queen
    for r in range(row):
        c = board[r]
        if c == col or abs(c - col) == abs(r - row):
            return False
    return True


def backtrack(row, board, n):
    """
    A recursive method that checks all possible
    configurations of the board row by row
    """
    # if it's the last row, print the board
    if row == n:
        print([[i, board[i]] for i in range(n)])
        return

    # iterate over the columns to find a safe spot
    # to place the queen, if not found, backtrack
    # to the previous row by returning from the method
    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col
            backtrack(row + 1, board, n)


def nqueens(n):
    """
    a method that solves the N queens problem

    Args:
        n (int): number of queens to place
    """

    # create a board of size n with values of -1
    board = [-1] * n

    # call the recursive method to solve the n queens problem
    backtrack(0, board, n)


def main():
    """
    Main function for the nqueens program
    """
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    nqueens(n)


if __name__ == "__main__":
    main()
