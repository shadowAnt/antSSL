#include "hmac.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// ./hmac sha224 fileName key
	
	char output[EVP_MAX_MD_SIZE];
	int outputLen;
	hmacEncodeFile(argv[1], argv[2], argv[3], output, &outputLen);
	int i;
	for(i = 0; i < outputLen; i++)
    {
        printf("%02x", (unsigned int)output[i]);
    }
    printf("\n");
	return 0;
}