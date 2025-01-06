#include <stdlib.h>
#include "lists.h"

/**
 * insert_node - inserts a number into a sorted singly linked list
 * @head: pointer to pointer of first node of listint_t list
 * @number: integer to be included in new node
 * Return: address of the new element or NULL if it fails
 */
listint_t *insert_node(listint_t **head, int number)
{
    listint_t *newNode, *currentNode, *prevNode;

    if (head == NULL)
        return (NULL);

    newNode = malloc(sizeof(listint_t));
    if (newNode == NULL)
        return (NULL);

    newNode->n = number;
    newNode->next = NULL;

    if (*head == NULL || (*head)->n >= number)
    {
        newNode->next = *head;
        *head = newNode;
        return (newNode);
    }

    currentNode = *head;
    while (currentNode != NULL && currentNode->n < number)
    {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    prevNode->next = newNode;
    newNode->next = currentNode;

    return (newNode);
}