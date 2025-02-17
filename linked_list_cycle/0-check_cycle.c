#include "lists.h"

/**
 * check_cycle - check if a single linked list 
 * loops back on itself
 * @list - pointer to the head of the list
 * Return: 0 if no cycle, 1 otherwise;
 */
int check_cycle(listint_t *list)
{
	listint_t *slowCursor = list;
	listint_t *fastCursor = list;
    
    while (fastCursor != NULL && fastCursor->next != NULL)
    {
        slowCursor = slowCursor->next;
        fastCursor = fastCursor->next->next;
        
        if (slowCursor == fastCursor)
            return (1);
    }
    
    return (0);
}