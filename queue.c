#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Allocate space for new element and set the value of all variables.
 * Return NULL pointer if could not allocate space.
 */
list_ele_t *list_ele_new(char *v, list_ele_t *n)
{
    /* Allocate space for new element*/
    list_ele_t *e = malloc(sizeof(list_ele_t));
    if (!e)
        return NULL;

    /* Allocate space for the value string and copy it */
    size_t vlen = strlen(v);
    e->value = malloc(vlen * sizeof(char) + 1);
    if (!e->value) {
        free(e);
        return NULL;
    }
    strncpy(e->value, v, vlen);
    e->value[vlen] = '\0';

    e->next = n;
    return e;
}

/*
 * Free all space for the element.
 */
void list_ele_free(list_ele_t *e)
{
    free(e->value);
    free(e);
}

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        list_ele_t *e = q->head;
        list_ele_t *next;
        while (e) {
            next = e->next;
            list_ele_free(e);
            e = next;
        }
        free(q);
    }
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q || !s)
        return false;

    /* Allocate space and copy string for new element*/
    list_ele_t *new = list_ele_new(s, q->head);
    if (!new)
        return false;

    /* Update list information */
    if (q->size == 0)
        q->tail = new;
    q->head = new;
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q || !s)
        return false;

    /* Allocate space and copy string for new element*/
    list_ele_t *new = list_ele_new(s, NULL);
    if (!new)
        return false;

    /* Update list information */
    if (q->size == 0)
        q->head = new;
    else
        q->tail->next = new;
    q->tail = new;
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    /* Copy the removed string to *sp */
    list_ele_t *rmv = q->head;
    if (sp) {
        size_t vlen = strlen(rmv->value);
        if (vlen > bufsize - 1)
            vlen = bufsize - 1;
        strncpy(sp, rmv->value, vlen);
        sp[vlen] = '\0';
    }

    /* Update list information */
    if (q->tail == rmv)
        q->tail = NULL;
    q->head = rmv->next;
    q->size--;

    list_ele_free(rmv);

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q || !q->head)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->size < 2)
        return;

    list_ele_t *e = q->head;
    list_ele_t *nxt, *pre = NULL;

    q->tail = e;
    while (e) {
        nxt = e->next;
        e->next = pre;
        pre = e;
        e = nxt;
    }
    q->head = pre;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
