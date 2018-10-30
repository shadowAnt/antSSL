
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

#define READ_SIZE 32768

int is_filename(char *name);

void print_hex_hash(unsigned char *digest, int length);

int sha224_file (char *path, unsigned char *digest);

void sha224_string(char *str, unsigned char *digest);

int sha256_file (char *path, unsigned char *digest);

void sha256_string(char *str, unsigned char *digest);

int sha384_file (char *path, unsigned char *digest);

void sha384_string(char *str, unsigned char *digest);

int sha512_file (char *path, unsigned char *digest);

void sha512_string(char *str, unsigned char *digest);

