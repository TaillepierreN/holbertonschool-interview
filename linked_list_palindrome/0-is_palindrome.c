#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * is_palindrome - Checks if a singly linked list is a palindrome.
 * @head: Double pointer to the head of the linked list.
 * Return: 1 if the list is palindrome,0 otherwise.
 */
int is_palindrome(listint_t **head)
{
    if (!head || !*head || !(*head)->next)
        return 1;

    listint_t *slowCursor = *head, *fastCursor = *head, *first_half, *second_half;

    while (fastCursor && fastCursor->next)
    {
        slowCursor = slowCursor->next;
        fastCursor = fastCursor->next->next;
    }

    second_half = reverse_list(slowCursor);
    first_half = *head;

    while (second_half)
    {
        if (first_half->n != second_half->n)
            return 0;

        first_half = first_half->next;
        second_half = second_half->next;
    }

    return 1;
}

/**
 * reverse_list - Reverses a singly linked list.
 * @head: Pointer to the head of the list to be reversed.
 * Return: Pointer to the head of the reversed list.
 */
listint_t *reverse_list(listint_t *head)
{
    listint_t *prev = NULL, *current = head, *next = NULL;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}
