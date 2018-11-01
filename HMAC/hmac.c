#include "hmac.h"

#define READSIZE 32768

int is_filename(char *name)
{
    if (access(name, F_OK) != -1)
        return 1;
    else
        return 0;
}

long getFileSize(FILE *file)
{
    fseek (file, 0, SEEK_END);
    long lSize;
    lSize = ftell(file);
    rewind (file);//point back to the begin
    printf("the size of file is : %ld byte\n", lSize);
    return lSize;
}

int hmacEncodeFile(char *mode, char *input, char *key, 
    char *output, int *outputLen)
{
    printf("the key is: %s, len is %ld\n", key, strlen(key));
    const EVP_MD *engine = NULL;
    if(strcasecmp("sha512", mode) == 0) engine = EVP_sha512();
    else if(strcasecmp("sha256", mode) == 0) engine = EVP_sha256();
    else if(strcasecmp("sha1", mode) == 0) engine = EVP_sha1();
    else if(strcasecmp("md5", mode) == 0) engine = EVP_md5();
    else if(strcasecmp("sha224", mode) == 0) engine = EVP_sha224();
    else if(strcasecmp("sha384", mode) == 0) engine = EVP_sha384();
    else
    {
        printf("Algorithm %s  is not supported by this program!\n", mode);
        return -1;
    }

    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);

    if(!is_filename(input))
    {
        printf("input is a string: %s\n", input);
        HMAC_Update(&ctx, (unsigned char*)input, strlen(input));
    }
    else
    {
        FILE *file = fopen(input, "rb");
        if (!file)
        {
            printf("can not open %s\n", input);
            return -1;
        }
        char *buffer = malloc(READSIZE);
        int bytes_read = 0;

        // int len;
        // len = getFileSize(file);
        // int onceSize = READSIZE;
        // for(; len > 0; len -= onceSize)
        // {
        //     if(len < READSIZE) onceSize = len;

        //     fread (buffer, 1, onceSize, file);
        //     HMAC_Update(&ctx, buffer, onceSize);
        // }
        while(bytes_read = fread(buffer, 1, READSIZE, file))
            HMAC_Update(&ctx, buffer, bytes_read);
    }

    HMAC_Final(&ctx, output, outputLen);
    // printf("%d\n", *outputLen);
    HMAC_CTX_cleanup(&ctx);
    return 0;
}