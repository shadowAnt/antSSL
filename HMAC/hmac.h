#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/hmac.h>

long getFileSize(FILE *file);

int hmacEncodeFile(char *fileName, char *key, char *mode, char *output, int *outputLen);
