/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* If malloc return Null, return NULL. */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *next_p;
    list_ele_t *next_next_p;
    next_p = q->head;

    while (next_p) {
        next_next_p = next_p->next;
        free(next_p->value);
        free(next_p);
        next_p = next_next_p;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* If queue is Null or fail to malloc, return false. */
    if (!q) {
        return false;
    }
    if (!(newh = malloc(sizeof(list_ele_t)))) {
        return false;
    }
    /* Allocate space for the string and copy it. */
    if (!(newh->value = malloc(sizeof(char) * (strlen(s) + 1)))) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    if (q->head == NULL) {
        q->tail = newh;
    }
    q->size++;
    newh->next = q->head;
    q->head = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;

    if (!q) {
        return false;
    }
    if (!(newt = malloc(sizeof(list_ele_t)))) {
        return false;
    }
    /* Allocate space for the string and copy it. */
    if (!(newt->value = malloc(sizeof(char) * (strlen(s) + 1)))) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    newt->next = NULL;
    q->size++;
    q->tail->next = newt;
    q->tail = newt;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *remove_ele;

    /* If queue is NULL or queue is empty, return false. */
    if (!q || !(q->head->value)) {
        return false;
    }

    remove_ele = q->head;
    if (sp) {
        strncpy(sp, remove_ele->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    q->size--;
    q->head = q->head->next;
    free(remove_ele->value);
    free(remove_ele);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    list_ele_t *prev;
    list_ele_t *next;
    list_ele_t *next_next;

    q->tail = q->head;
    prev = q->head;
    next = q->head->next;
    q->head->next = NULL;
    while (1) {
        next_next = next->next;
        next->next = prev;
        prev = next;
        next = next_next;
        if (next == NULL) {
            q->head = prev;
            break;
        }
    }
}
