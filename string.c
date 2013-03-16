#include <string.h>
#include <stdlib.h>
#include "struct.h"

/* two parameters: pattern string, next array */
void string_kmp_get_next(str_t *t, int *next)
{
    int   i, j;
    char *p;
    
    i = 0;
    j = -1;
    next[0] = -1;
    p = t->data;
    
    while (i < t->len) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            //next[i] = (p[i] != p[j]) ? j : next[j];
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int string_kmp(str_t *s, str_t *t)
{
    int   *next;
    char  *p1;
    char  *p2;
    int    i, j;
    int    rc = -1;
    int    len;
    
    if (!s || !t) {
        return -1;
    }

    len = s->len * sizeof(int);
    
    next = malloc(len);
    if (!next) {
        return rc;
    }
    
    string_kmp_get_next(t, next);

    p1 = s->data;
    p2 = t->data;
    
    i = 0;
    j = 0;
    
    while (i < s->len && j < t->len) {
        if (j == -1) {
            j++;
        }
        
        if (p1[i] == p2[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j == t->len) {
        rc = i - t->len;
    } else {
        rc = -1;
    }

    return rc;
}

