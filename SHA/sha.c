#include "sha.h"

/**
 * the name is a filename or not?
 * @param  name [description]
 * @return      [description]
 */
int is_filename(char *name)
{
    if (access(name, F_OK) != -1)
        return 1;
    else
        return 0;
}

/**
 * [print_hex_hash ]
 * @param digest [description]
 * @param length [description]
 */
void print_hex_hash(unsigned char *digest, int length)
{
    int i;
    for(i = 0; i < length; i++)
        printf("%02x", digest[i]);
}

/**
 * sha224(file)
 * @param  path   [the path of file]
 * @param  digest [return]
 * @return        [0 is success]
 */
int sha224_file (char *path, unsigned char *digest)
{
    char hash[SHA224_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char *buffer = NULL;
    const int bufsize = READ_SIZE;
    int bytes_read = 0;

    FILE *file = fopen(path, "rb");
    if (!file)
    {
        printf("%s: can not open %s\n", __func__, path);
        return -1;
    }

    SHA224_Init(&sha256);

    buffer = malloc(bufsize);
    if (!buffer)
    {
        printf("%s: malloc failed\n", __func__);
        fclose(file);
        return -1;
    }

    while((bytes_read = fread(buffer, 1, bufsize, file)))
        SHA224_Update(&sha256, buffer, bytes_read);

    SHA224_Final(digest, &sha256);

    fclose(file);
    free(buffer);

    return 0;
}

/**
 * sha224(string)
 * @param str    [description]
 * @param digest [description]
 */
void sha224_string(char *str, unsigned char *digest)
{
    SHA256_CTX c;
    SHA224_Init(&c);
    SHA224_Update(&c, str, strlen(str));
    SHA224_Final(digest, &c);
}

int sha256_file (char* path, unsigned char *digest)
{
	char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	char *buffer = NULL;
	const int bufsize = READ_SIZE;
	int bytes_read = 0;

	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("%s: can not open %s\n", __func__, path);
		return -1;
	}

	SHA256_Init(&sha256);

	buffer = malloc(bufsize);
	if (!buffer) {
		printf("%s: malloc failed\n", __func__);
		fclose(file);
		return -1;
	}

	while((bytes_read = fread(buffer, 1, bufsize, file)))
		SHA256_Update(&sha256, buffer, bytes_read);

	SHA256_Final(digest, &sha256);

	fclose(file);
	free(buffer);

	return 0;
}

void sha256_string(char* str, unsigned char *digest)
{
	SHA256_CTX c;
	SHA256_Init(&c);
	SHA256_Update(&c, str, strlen(str));
	SHA256_Final(digest, &c);
}

int sha384_file (char* path, unsigned char *digest)
{
	char hash[SHA384_DIGEST_LENGTH];
	SHA512_CTX sha512;
	char *buffer = NULL;
	const int bufsize = READ_SIZE;
	int bytes_read = 0;

	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("%s: can not open %s\n", __func__, path);
		return -1;
	}

	SHA384_Init(&sha512);

	buffer = malloc(bufsize);
	if (!buffer) {
		printf("%s: malloc failed\n", __func__);
		fclose(file);
		return -1;
	}

	while((bytes_read = fread(buffer, 1, bufsize, file)))
		SHA384_Update(&sha512, buffer, bytes_read);

	SHA384_Final(digest, &sha512);

	fclose(file);
	free(buffer);

	return 0;
}

void sha384_string(char* str, unsigned char *digest)
{
	SHA512_CTX c;
	SHA384_Init(&c);
	SHA384_Update(&c, str, strlen(str));
	SHA384_Final(digest, &c);
}

int sha512_file (char* path, unsigned char *digest)
{
	char hash[SHA512_DIGEST_LENGTH];
	SHA512_CTX sha512;
	char *buffer = NULL;
	const int bufsize = READ_SIZE;
	int bytes_read = 0;

	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("%s: can not open %s\n", __func__, path);
		return -1;
	}

	SHA512_Init(&sha512);

	buffer = malloc(bufsize);
	if (!buffer) {
		printf("%s: malloc failed\n", __func__);
		fclose(file);
		return -1;
	}

	while((bytes_read = fread(buffer, 1, bufsize, file)))
		SHA512_Update(&sha512, buffer, bytes_read);

	SHA512_Final(digest, &sha512);

	fclose(file);
	free(buffer);

	return 0;
}

void sha512_string(char* str, unsigned char *digest)
{
	SHA512_CTX c;
	SHA512_Init(&c);
	SHA512_Update(&c, str, strlen(str));
	SHA512_Final(digest, &c);
}