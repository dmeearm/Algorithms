#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

inline void sort_print(int *data, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");
    
    return;
}

void sort_insert(int *data, int len)
{
    int tmp;
    int i;
    int j;

    if (len < 1) {
        return;
    }
    
    for (i = 1; i < len - 1; i++) {
        tmp = data[i];
        for (j = i - 1; j >= 0; j--) {
            if (data[j] > tmp) {
                data[j + 1] = data[j];
            } else {
                break;
            }
        }

        data[j + 1] = tmp;
    }

    return;
}

void sort_bubble(int *data, int len)
{
    int i;
    int j;
    int tmp;
    int change;

    for (i = 0; i < len - 1; i++) {
        change = 0;
        for (j = i + 1; j < len; j++) {
            if (data[i] > data[j]) {
                tmp = data[j];
                data[j] = data[i];
                data[i] = tmp;
                change = 1;
            }
        }

        if (change == 0) {
            break;
        }
    }
}

void sort_shell(int *data, int len)
{
    int gap;
    int i;
    int j;
    int k;
    int tmp;

    gap = len / 2;

    while (gap) {

        for (i = gap; i < len; i++) {
            tmp = data[i];
            for (j = i - gap; j >=0; j -= gap) {
                if (data[j] > tmp) {
                    data[j + gap] = data[j];
                } else {
                    break;
                }
            }
            data[j + gap] = tmp;
        }
        
        gap /= 2; 
    }

    return;
}

void sort_quick(int *data, int start, int end)
{
    int base;
    int i;
    int j;
    int tmp;
    
    if (start >= end) {
        return;
    }

    base = data[start];
    i = start;
    j = end;

    while (i < j) {
        
        while (j > i && data[j] >= base) {
            j--;
        }
        
        data[i] = data[j];
        
        while (i < j && data[i] <= base) {
            i++;
        }
        
        data[j] = data[i];
    }

    data[i] = base;
    
    sort_quick(data, start, i - 1);
    sort_quick(data, i + 1, end);

    return;
}

void sort_select(int *data, int len)
{
    int i;
    int j;
    int tmp;

    if (!data || !len) {
        return;
    }

    for (i = 0; i < len - 1; i++) {
        
        for (j = i + 1; j < len; j++) {
            
            if (data[i] > data[j]) {
                tmp = data[j];
                data[j] = data[i];
                data[i] = tmp;
            }
        }
    }
}

static void heap_shift1(int *data, int low, int high)
{
    int p;
    int c1;
    int c2;
    int maxc;
    int tmp;

    p = low;
    c1 = (low << 1);
    c2 = c1 + 1;

    while (c1 <= high) {
        
        if (c2 > high) {
            maxc = c1;
        } else {
            maxc = data[c1] < data[c2] ? c2 : c1;
        }
        
        if (data[maxc] < data[p]) {
            break;
        }
        
        tmp = data[p];
        data[p] = data[maxc];
        data[maxc] = tmp;
        
        p = maxc;
        c1 = (maxc << 1);
        c2 = c1 + 1;
    }  
}

void sort_heap1(int *data, int len)
{
    int i;
    int tmp;
    
    for (i = (len - 1) >> 1; i > 0; i--) {
        heap_shift1(data, i, len - 1);
    }
    
    for (i = len - 1; i > 1; i--) {
        
        tmp = data[i];
        data[i] = data[1];
        data[1] = tmp;
        
        heap_shift1(data, 1, i - 1);
    }
}

static heap_shift2(int *data, int low, int high)
{
    int p;
    int c1;
    int c2; 
    int max;
    int tmp;

    p = low;
    c1 = (low << 1) + 1;
    c2 = c1 + 1;

    while (c1 <= high) {
        if (c2 > high) {
            max = c1;
        } else {
            max = data[c1] > data[c2] ? c1 : c2; 
        }

        if (data[max] < data[p]) {
            break;
        }

        tmp = data[p];
        data[p] = data[max];
        data[max] = tmp;

        p = max;
        c1 = (max << 1) + 1;
        c2 = c1 + 1;
    }
}

void sort_heap2(int *data, int len)
{
    int i;
    int tmp;

    for (i = (len >> 1); i >= 0; i--) {
        heap_shift2(data, i, len - 1);
    }
    
    for (i = len - 1; i >= 0; i--) {
        
        tmp = data[i];
        data[i] = data[0];
        data[0] = tmp;
        
        heap_shift2(data, 0, i - 1);
    }
}

static merge(int *data, int low, int mid, int high)
{
    int *tmp;
    int  size;
    int  i;
    int  j;

    size = high - low + 1;

    if (size <= 0 || mid < low || mid > high) {
        return;
    }

    tmp = malloc(size * sizeof(int));
    if (!tmp) {
        return;
    }
    
    i = low;
    j = mid + 1;
    size = 0;
    
    while (i <= mid && j <= high) {
        if (data[i] < data[j]) {
            tmp[size] = data[i];
            i++;
        } else {
            tmp[size] = data[j];
            j++;
        }
        size++;
    }

    while (i <= mid) {
        tmp[size] = data[i];
        i++;
        size++;
    }
    
    while (j <= high) {
        tmp[size] = data[j];
        j++;
        size++;
    }

    for (i = low, j = 0; i <= high; i++, j++ ) {
        data[i] = tmp[j];
    }

    free(tmp);
    
    return; 
}

void merge_pass(int *data, int len, int size)
{
    int i;

    for (i = 0; i + (size << 1) - 1 < len; i += (size << 1)) {
        merge(data, i, i + size - 1,  i + (size << 1) - 1);
    }

    if (i + size - 1 < len) {
        merge(data, i, i + size - 1, len - 1);
    }

    return;
}

// merge algorithm for down to up
void sort_merge1(int *data, int len)
{
    int length;

    for (length = 1; length < len; length *= 2) {
        merge_pass(data, len, length);
    }

    return;
}

// merge algorithm from up to down
void sort_merge2(int *data, int low, int high)
{
    int mid;
    
    if (low < high) {
        mid = low + (high - low) / 2;
        sort_merge2(data, low, mid);
        sort_merge2(data, mid + 1, high);
        merge(data, low, mid, high);
    }

    return;
}

void sort_radix()
{
}
