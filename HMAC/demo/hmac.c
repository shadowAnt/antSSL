#include "hmac.h"

#define READSIZE 32768

long getFileSize(FILE *file)
{
	fseek (file, 0, SEEK_END);
    long lSize;
    lSize = ftell(file);
    rewind (file);//point back to the begin
    printf("the size of file is : %ld byte\n", lSize);
    return lSize;
}

int hmacEncodeFile(char *mode, char *fileName, char *key, char *output, int *outputLen)
{
	EVP_MD *engine = NULL;
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
	FILE *file = fopen(fileName, "rb");
	if (!file) {
		printf("can not open %s\n", fileName);
		return -1;
	}
	int len;
	len = getFileSize(file);
	HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);

    char *buffer = malloc(READSIZE);
    int bytes_read = 0;
    // int onceSize = READSIZE;
    // for(; len > 0; len -= onceSize)
    // {
    //     if(len < READSIZE) onceSize = len;

    //     fread (buffer, 1, onceSize, file);
    //     HMAC_Update(&ctx, buffer, onceSize);   
    // }
	while(bytes_read = fread(buffer, 1, READSIZE, file))
		HMAC_Update(&ctx, buffer, bytes_read);   

    output = (unsigned char *)malloc(EVP_MAX_MD_SIZE);
 	HMAC_Final(&ctx, output, outputLen);
    HMAC_CTX_cleanup(&ctx);
    return 0;
}