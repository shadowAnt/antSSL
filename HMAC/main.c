#include "hmac.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // ./hmac sha224 fileName key

    if(argc != 4)
    {
        printf("format ERROR ./hmac sha224 input key\n");
    }
    unsigned char *output = (unsigned char *)malloc(EVP_MAX_MD_SIZE);
    int outputLen = 0;
    hmacEncodeFile(argv[1], argv[2], argv[3], output, &outputLen);
    int i;
    for(i = 0; i < outputLen; i++)
    {
        printf("%02x", output[i]);
    }
    printf("\n");
    free(output);
    return 0;
}