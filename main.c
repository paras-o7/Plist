#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

#define CHAR_TYPE  0x01
#define INT_TYPE   0x02
#define FLOAT_TYPE 0x04

void insert_int_into_list(Plist l, int i) {
    int *p = malloc(sizeof (int));
    *p = i;
    append(l, p, INT_TYPE);
}
void insert_float_into_list(Plist l, float i) {
    float *p = malloc(sizeof (float));
    *p = i;
    append(l, p, FLOAT_TYPE);
}
void insert_char_into_list(Plist l, char i) {
    char *p = malloc(sizeof (char));
    *p = i;
    append(l, p, CHAR_TYPE);
}

int main(void) {
    Plist list = create();
    insert_char_into_list(list, 'P');
    insert_int_into_list(list, 255);
    insert_float_into_list(list, 9.8f);
    insert_float_into_list(list, 3.14f);

    struct filament f;
    for (int i = 0; i < 4; i++) {
        printf("%d\t", i);
        f = pop(list);
        if (f.bm & CHAR_TYPE)
            printf("char\t%c\n", * ((char *) f.elem));
        else if (f.bm & INT_TYPE)
            printf("int\t%d\n", * ((int *) f.elem));
        if (f.bm & FLOAT_TYPE)
            printf("float\t%f\n", * ((float *) f.elem));

        free(f.elem);
   }

   puts("Finished");
   destroy(list, free);
   return 0;
}