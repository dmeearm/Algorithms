/*
 * a sample of BLOWFISH encrypt
 * CFLAGS = -lssl
 */

#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

char *bin2hex(unsigned char *data, int len, char *str)
{
	char *hex = "0123456789abcdef";
	int i, k;

	for(i = 0; i < len; i++) {
		k = i << 1;
		str[k] = hex[data[i] >> 4];
		str[k + 1] = hex[data[i] & 0xf];
	}
	str[k + 2] = '\0';

	return str;
}

int inline c2n(char c)
{
	if('0' <= c && c <= '9')
		return c - '0';
	if('a' <= c && c <= 'f')
		return c - 'a' + 10;
	if('A' <= c && c <= 'F')
		return c - 'A' + 10;
	return -1;

}
int hex2bin(unsigned char *bin, const char *hex, int len)
{
	int i, k, r;

	if(len & 1) {
		return -1;
	}

	k = 0;
	for(i = 0; i < len; i += 2) {
		r = c2n(hex[i]);
		if(r == -1)
			return -1;
		bin[k] = r << 4;

		r = c2n(hex[i + 1]);
		if(r == -1)
			return -1;
		bin[k] |= r;

		k++;
	}

	return 0;
}

int blowfish_encrypt(unsigned char *out_buf,
		const unsigned char *data, int data_len,
		const unsigned char *key, int ken_len)
{
	EVP_CIPHER_CTX ctx;
	int out_len, out_tail_len;
	int rc;

	EVP_CIPHER_CTX_init(&ctx);

	rc = EVP_EncryptInit_ex(&ctx, EVP_bf_ecb(), NULL, NULL, NULL);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = EVP_CIPHER_CTX_set_key_length(&ctx, ken_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = EVP_EncryptInit_ex(&ctx, NULL, NULL, key, NULL);
	if(rc == 0) {
		rc = -1;
		goto out;
	}

	rc = EVP_EncryptUpdate(&ctx, out_buf, &out_len, data, data_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}

	rc = EVP_EncryptFinal_ex(&ctx, out_buf + out_len, &out_tail_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = out_len + out_tail_len;

out:
	EVP_CIPHER_CTX_cleanup(&ctx);
	return rc;
}

int blowfish_decrypt(unsigned char *out_buf,
		const unsigned char *data, int data_len,
		const unsigned char *key, int ken_len)
{
	EVP_CIPHER_CTX ctx;
	int out_len, out_tail_len;
	int rc;

	EVP_CIPHER_CTX_init(&ctx);

	rc = EVP_DecryptInit_ex(&ctx, EVP_bf_ecb(), NULL, NULL, NULL);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = EVP_CIPHER_CTX_set_key_length(&ctx, ken_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = EVP_DecryptInit_ex(&ctx, NULL, NULL, key, NULL);
	if(rc == 0) {
		rc = -1;
		goto out;
	}

	rc = EVP_DecryptUpdate(&ctx, out_buf, &out_len, data, data_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}

	rc = EVP_DecryptFinal_ex(&ctx, out_buf + out_len, &out_tail_len);
	if(rc == 0) {
		rc = -1;
		goto out;
	}
	rc = out_len + out_tail_len;

out:
	EVP_CIPHER_CTX_cleanup(&ctx);
	return rc;
}


void encrypt(char *str, char *key)
{
	char out_buf[1000];
	char hex[2000];
	int ret;
	int len;

	len = strlen(str);
	ret = blowfish_encrypt(out_buf, str, len, key, strlen(key));
	if(ret < 0) {
		printf("encrypt error!\n");
		return;
	}

	bin2hex(out_buf, ret, hex);
	printf("encrypt: %s -> %s\n", str, hex);
}


void decrypt(char *xcode, char *key)
{
	char xcode_bin[100];
	char out_buf[1000];
	int ret;
	int len;

	len = strlen(xcode);

	ret = hex2bin(xcode_bin, xcode, len);
	if(ret < 0) {
		printf("decrypt error!\n");
		return;
	}

	ret = blowfish_decrypt(out_buf, xcode_bin, len/2, key, strlen(key));
	if(ret == -1) {
		printf ("decrypt error!!\n");
		return;
	}
	out_buf[ret] = '\0';

	printf("decrypt: %s -> %s\n", xcode, out_buf);
}


int main()
{
	char *key = "pcscdn";

	char *str = "test string";

	char *hex = "f20f50ed8f146ccb574c89e07017a3f4";

	encrypt(str, key);
	
	decrypt(hex, key);

	return 0;
}

