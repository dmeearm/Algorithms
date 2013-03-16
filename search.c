#include "struct.h"

int bin_search(int *s, int len, int key)
{
    int low;
    int mid;
    int high;
    
    low = 0;
    high = len - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (s[mid] == key) {
            return mid;
        } else if (s[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

