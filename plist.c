#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "plist.h"

#define _PRINT_MALLOC_ERR()                                  \
    fprintf(                                                 \
        stderr,                                              \
        "ERROR!! Failed to allocate memory at %s::%s():%d",  \
        __FILE__,                                            \
        __func__,                                            \
        __LINE__                                             \
    )

struct node {
    struct filament filament;
    struct node *next;
};

struct Plist_ {
    struct node *first, *last;
    size_t n;
};

static inline struct node *alloc_new_node(void *elem, Bitmask bm, size_t size) {
    struct node *_ = malloc(sizeof *_);
    if (_) {
        _->filament.elem = elem;
        _->filament.bm = bm;
        _->filament.size = size;
        _->next = NULL;
    }
    return _;
}

/* 
 * create(): Initialize a Plist ADT
 */
struct Plist_ *create(void) {
    struct Plist_ *l = malloc(sizeof (struct Plist_));
    if (!l)
        _PRINT_MALLOC_ERR();
    else {
        l->first = l->last = NULL;
        l->n = 0;
    }
    return l;
}

/*
 * destroy: Destroy a Plist ADT
 *     Arguments:
 *     - struct Plist_ *l: The ADT to be destroyed
 *     - void (*destroy_element)(void *): Function to 
 *       destroy the element stored in the list
 */
void destroy(struct Plist_ *l, void (*destroy_element)(void *)) {
    if (l->last) {
        struct node *tmp;
        while (l->last) {
            tmp = l->last;
            l->last = l->last->next;
            (*destroy_element)(tmp->filament.elem);
            free(tmp);
        }
    }
    free(l);
}

/*
 * append: Push an element into the list
 *     Arguments:
 *     - struct Plist_ *l: ADT
 *     - void *elemptr: Pointer to element to be pushed
 *     - Bitmask bm: Bitmask to identify the type
 *     - size_t size: number of bytes used by the element
 */
bool append(struct Plist_ *l, void *elemptr, Bitmask bm, size_t size) {
    struct node *n = alloc_new_node(elemptr, bm, size);
    if (!n) {
        _PRINT_MALLOC_ERR();
        return false;
    }

    if (!l->first && !l->last)
        l->first = n;

    n->next = l->last;
    l->last = n;
    l->n++;
    return true;
}

/*
 * pop: Remove the last element from the list
 *     Arguments:
 *     - struct Plist_ *l: ADT
 * WARNING: The user is required to handle
 * the destruction of the element
 */
struct filament pop(struct Plist_ *l) {
    if (!l->last && !l->first)
        return (struct filament) {NULL, 0, 0};

    struct node *n = l->last;
    struct filament f = n->filament;
    l->last = l->last->next;

    if (!l->last) l->first = NULL;

    free(n);
    l->n--;
    return f;
}

/* length: Get length of the list */
size_t length(struct Plist_ *l) {
    return l->n;
}

/*
 * clear: Make the list empty
 *     - Arguments: struct Plist_ *l: ADT
 */
void clear(struct Plist_ *l, void (*destroy_element)(void *)) {
    struct node *tmp;
    while (l->last) {
        tmp = l->last;
        l->last = l->last->next;
        (*destroy_element)(tmp->filament.elem);
        free(tmp);
    }
    l->first = NULL;
}

/*
 * index
 */
// size_t indexof(struct Plist_ *l, void *elem, size_t size) {
//     struct node *n = l->last;
//     size_t i = l->n;
//     while (n) {
//         if (
//             size == n->filament.size && 
//             memcmp(elem, n->filament.elem, size)
//         ) break;
//         n = n->next;
//         i--;
//     }
//     return i;
// }