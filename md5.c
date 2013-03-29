#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <openssl/md5.h>

int testMD5(unsigned char *res, unsigned char *keystr, size_t length)
{
    int          rv = 0;
    MD5_CTX      md5ctx;

    MD5_Init(&md5ctx);

    rv = MD5_Update(&md5ctx, keystr, length);
    if (!rv) {
     return -1;
    }

    rv = MD5_Final(res, &md5ctx);
    if (!rv) {
        return -1;
    }

    return 0;
}

/* Need a string argument to encode */
int main(int argc, char **argv)
{
    int            i;
    int            rv = 0;
    unsigned char  rawMD5[16];
    unsigned char  hexMD5[33];
    uint32_t       xcode;

    unsigned char  xtoc[] = "0123456789abcdef";

    if (argc != 2) {
        printf("It need one string argument\n");
        return -1;
    }

    rv = testMD5(rawMD5, (unsigned char *)argv[1], strlen(argv[1]));
    if (rv != 0) {
        return -1;
    }
    /* 
     * if have only one string, we can use "MD5" to calculate:
     * MD5((unsigned char *)argv[1], strlen(argv[1]), rawMD5);
     */
    for (i = 0; i < 16; i++) {
        hexMD5[2 * i] = xtoc[rawMD5[i] >> 4];
        hexMD5[2 * i + 1] = xtoc[rawMD5[i] & 0xf];
    }

    hexMD5[32] = '\0';

    printf("MD5 result: %s\n", hexMD5);

    return 0;
}
