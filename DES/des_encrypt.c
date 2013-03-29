#include "des.h"
#include <string.h>
#include <stdio.h>


#define CLP_LEN  16

void byte2hex(unsigned char *c, int len, unsigned char *dst)
{
    int               i;
    unsigned char     xtoc[] = "0123456789abcdef";
    
    for (i = 0; i < len; ++i) {
        dst[2 * i + 0] = xtoc[c[i] >> 4];
	    dst[2 * i + 1] = xtoc[c[i] & 0xf];
	}
    
	return;
}

int main(int argc, char **argv)
{
    int            i;
	unsigned char *p;
	unsigned char *s;
	int            len;
    unsigned char  key[8];
    unsigned char  last[8];
	unsigned char  result[8];
    unsigned char  ciphertext[64 * CLP_LEN + 1]; /* 1024 */
    unsigned char *end;
    gl_des_ctx     context;

    if (argc != 3) {
	    printf("it's need two arguments: key and plaintext\n");
		return 0;
	}
    
	if (strlen(argv[1]) > 8) {
        printf("the key must less than eight characters!\n");
		return 0;
	}

	memset(key, 0, 8);

	memcpy(key, argv[1], strlen(argv[1]));

    gl_des_setkey(&context, (const char *)key);
    
	len = strlen(argv[2]);
	s = (unsigned char *)argv[2];
    p = ciphertext;
    end = p + 64 * CLP_LEN;
    for (i = 0; i < len; i += 8) {
        /* the buffer is full */
        if (p == end) {
            break;
        }
        
	    if (len - i < 8) {
		    memset(last, 0, 8);
			memcpy(last, s, len - i);
			s = last;
		}

        gl_des_ecb_encrypt(&context, (const char *)s, (char *)result);
	    byte2hex((unsigned char *)result, 8, p);
        
		p += 16;
		s += 8;
	}

    *p = 0;

    printf("%s\n", ciphertext);
    
    return 0;
}
