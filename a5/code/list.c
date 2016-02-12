#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

struct list {
  element_t head, tail;
};

struct element {
  char*     value;
  element_t prev, next;

  int refs;
};

void element_inc_ref(element_t e) {
  if (e == NULL) {
    return;
  }
  e->refs += 1;
}
void element_dec_ref(element_t e) {
  if (e == NULL) {
    return;
  }
  e->refs -= 1;
  if (e->refs <= 0) {
    free(e->value);
    free(e);
  }
}

/**
 * Create new list
 */
list_t list_new() {
  list_t l = malloc (sizeof (*l));
  l->head = l->tail = NULL;
  return l;
}

/**
 * Delete the list (including its elements).
 */
void list_delete (list_t l) {
  for (element_t e = l->head, n; e != NULL; e = n) {
    n = e->next;
    list_delete_element (l, e);
  }
  free (l);
}

/**
 * Add an element to the list.
 * Returns pointer to new element.
 * NOTE: Returned element is not owned by caller; call inc_ref if reference is saved.
 */
element_t list_add_element (list_t l, char* value) {
  element_t e = malloc (sizeof (*e));
  e->refs = 0;
  e->value    = strdup (value);
  e->prev = e->next = NULL;
  if (l->head == NULL) {
    element_inc_ref(e);
    element_dec_ref(l->head);
    l->head = e;
  } else {
    element_inc_ref(e);
    element_dec_ref(l->tail->next);
    l->tail->next = e;

    element_inc_ref(l->tail);
    element_dec_ref(e->prev);
    e->prev       = l->tail;
  }
  element_inc_ref(e);
  element_dec_ref(l->tail);
  l->tail = e;
  return e;
}

/**
 * Remove element from list and free it
 */
void list_delete_element (list_t l, element_t e) {
  if (e == l->head) {
    element_inc_ref(e->next);
    l->head = e->next;
  } else {
    element_inc_ref(e->next);
    e->prev->next = e->next;
  }
  if (e == l->tail) {
    element_inc_ref(e->prev);
    l->tail = e->prev;
  } else {
    element_inc_ref(e->prev);
    e->next->prev = e->prev;
  }
  element_dec_ref(e->next);
  element_dec_ref(e->prev);
  e->next = e->prev = NULL;
  element_dec_ref(e);
  element_dec_ref(e);
}

/**
 * Get first element of list.
 * NOTE: Returned element is not owned by caller; call inc_ref if reference is saved.
 */
element_t list_get_first_element (list_t l) {
  return l->head;
}

/**
 * Get next element of list.
 * NOTE: Returned element is not owned by caller; call inc_ref if reference is saved.
 */
element_t element_get_next (element_t e) {
  return e->next;
}

/**
 * Get element's value
 */
char* element_get_value (element_t e) {
  return e->value;
}
