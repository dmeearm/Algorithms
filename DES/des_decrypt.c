#include <stdio.h>
#include <string.h>
#include "des.h"

int hex2byte(unsigned char *s, int len, unsigned char *dst)
{
    int            i = 0;
    unsigned char  decode = 0;
    unsigned char  c = 0;
    unsigned char *p = NULL;


    if (len % 2 != 0) {
        return -1;
    }

    p = dst;
    
    while (i < len) {

        /* first char of peer hex character */
        if (s[i] >= '0' && s[i] <= '9') {
            decode = (unsigned char)(s[i] - '0');
        } else {
            c = (unsigned char)(s[i] | 0x20);
            if (c >= 'a' && c <= 'f') {
                decode = (unsigned char)(c - 'a' + 10);
            } else {
                /* invalid character */
                return -1;
            }
        }

        /* second char of peer hex character */
        c = s[i + 1];
        if (c >= '0' && c <= '9') {
            *p = (unsigned char)((decode << 4) + c - '0');
        } else {
            c = (unsigned char)(c | 0x20);
            if (c >= 'a' && c <= 'f') {
                *p = (unsigned char)((decode << 4) + c - 'a' + 10);
            } else {
                /* invalid character */
                return -1;
            }
        }
        
        i += 2;
        p++;
    }

    return p - dst;
}

int main(int argc, char **argv)
{
    char            key[8];
    unsigned char   result[8];
    unsigned char   recoverd[513];
    int             len;
    int             i;
    unsigned char  *p;
    unsigned char  *res;
    int             rv = 0;

    gl_des_ctx context;

    if (argc != 3) {
        printf("it's need two arguments: key and ciphertext\n");
        return 0;
    }
    
    if (strlen(argv[1]) > 8) {
        printf("the key must less than eight characters\n");
        return 0;
    }

    len = strlen(argv[2]);
    if (len % 16 != 0 || len > 1024) {
        printf("invalid ciphertext\n");
        return 0;
    }
    
    memset(key, 0, 8);

    memcpy(key, argv[1], strlen(argv[1]));
    
    gl_des_setkey(&context, (const char *)key);

    memset(recoverd, 0, sizeof(recoverd));

    p = (unsigned char *)(argv[2]);
    res = recoverd;
    for (i = 0; i < len; i += 16) {
        
        memset(result, 0, 8);
        
        rv = hex2byte(p, 16, result);
        if (rv < 0) {
            printf("DES decrypt failed\n");
            return 0;
        }

        rv = gl_des_ecb_decrypt(&context, (const char *)result, (char *)res);

        res += rv;
        p += 16;
    }
    
    printf("the plain text is: %s\n", recoverd);

    return 0;
}
