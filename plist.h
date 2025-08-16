#ifndef PLIST_H
#define PLIST_H

#include <stdbool.h>

typedef unsigned long long Bitmask;
typedef struct Plist_ *Plist;

struct filament {
    void *elem;
    Bitmask bm;
    size_t size;
};

Plist create(void);
void destroy(Plist l, void (*destroy_element)(void *));

bool append(Plist l, void *elemptr, Bitmask bm, size_t size);
struct filament pop(Plist l);

size_t length(Plist l);

void clear(Plist l, void (*destroy_element)(void *));

#endif