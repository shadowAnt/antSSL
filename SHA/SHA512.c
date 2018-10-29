
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

static int is_filename(char *name)
{
	if (access(name, F_OK) != -1)
		return 1;
	else
		return 0;
}

#define READ_SIZE 32768
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

void print_hex_hash(unsigned char* digest, int length)
{
	int i;
	for(i=0; i < length; i++)
		printf("%02x", digest[i]);
}

int main(int argc, char *argv[])
{
	unsigned char sha512_digest[SHA512_DIGEST_LENGTH];
	int i = 0;

	for (i = 1; i < argc; i++) {
		if (is_filename(argv[i])) {
			printf("File('%s'): ", argv[i]);
			sha512_file(argv[i], sha512_digest);
		} else {
			printf("String('%s'): ", argv[i]);
			sha512_string(argv[i], sha512_digest);
		}
		print_hex_hash(sha512_digest, SHA512_DIGEST_LENGTH);
		printf("\n");
	}

	return 0;
}