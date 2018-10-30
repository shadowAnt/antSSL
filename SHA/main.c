#include "sha.h"

//./sha sha224 1.txt   or   ./sha sha224 asdc

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("the num of parameter should be 2, such as ./sha sha224 1.txt\n");
        return 1;
    }
    if(strcasecmp(argv[1], "sha224") == 0)
    {
        unsigned char sha224_digest[SHA224_DIGEST_LENGTH];
        int i = 0;

        for (i = 2; i < argc; i++)
        {
            if (is_filename(argv[i]))
            {
                printf("File('%s'): ", argv[i]);
                sha224_file(argv[i], sha224_digest);
            }
            else
            {
                printf("String('%s'): ", argv[i]);
                sha224_string(argv[i], sha224_digest);
            }
            print_hex_hash(sha224_digest, SHA224_DIGEST_LENGTH);
            printf("\n");
        }
    }
    else if(strcasecmp(argv[1], "sha256") == 0)
    {
        unsigned char sha256_digest[SHA256_DIGEST_LENGTH];
        int i = 0;

        for (i = 2; i < argc; i++)
        {
            if (is_filename(argv[i]))
            {
                printf("File('%s'): ", argv[i]);
                sha256_file(argv[i], sha256_digest);
            }
            else
            {
                printf("String('%s'): ", argv[i]);
                sha256_string(argv[i], sha256_digest);
            }
            print_hex_hash(sha256_digest, SHA256_DIGEST_LENGTH);
            printf("\n");
        }
    }
    else if(strcasecmp(argv[1], "sha384") == 0)
    {
        unsigned char sha384_digest[SHA384_DIGEST_LENGTH];
        int i = 0;

        for (i = 2; i < argc; i++)
        {
            if (is_filename(argv[i]))
            {
                printf("File('%s'): ", argv[i]);
                sha384_file(argv[i], sha384_digest);
            }
            else
            {
                printf("String('%s'): ", argv[i]);
                sha384_string(argv[i], sha384_digest);
            }
            print_hex_hash(sha384_digest, SHA384_DIGEST_LENGTH);
            printf("\n");
        }
    }
    else if(strcasecmp(argv[1], "sha512") == 0)
    {
        unsigned char sha512_digest[SHA512_DIGEST_LENGTH];
        int i = 0;

        for (i = 2; i < argc; i++)
        {
            if (is_filename(argv[i]))
            {
                printf("File('%s'): ", argv[i]);
                sha512_file(argv[i], sha512_digest);
            }
            else
            {
                printf("String('%s'): ", argv[i]);
                sha512_string(argv[i], sha512_digest);
            }
            print_hex_hash(sha512_digest, SHA512_DIGEST_LENGTH);
            printf("\n");
        }
    }
    else
    {
        printf("choose sha224 sha256 sha384 sha512\n");
        return 1;
    }
    return 0;
}