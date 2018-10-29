//gcc hmac_demo1.c -o hmac_demo1 -lcrypto
 
#include <stdio.h>
#include <string.h>
#include <openssl/hmac.h>
 
int main()
{
    // The key to hash
    char key[] = "012345678";
 
    // The data that we're going to hash using HMAC
    char data[] = "hello world";
 
    unsigned char digest[EVP_MAX_MD_SIZE] = {'\0'};
    unsigned int digest_len = 0;
 
    // Using sha1 hash engine here.
    // You may use other hash engines. e.g EVP_md5(), EVP_sha224, EVP_sha512, etc
    HMAC(EVP_sha1(), key, strlen(key), (unsigned char*)data, strlen(data), digest, &digest_len);
    printf("%s, len %u\n", digest, digest_len);
 
    // Be careful of the length of string with the choosen hash engine. SHA1 produces a 20-byte hash value which rendered as 40 characters.
    // Change the length accordingly with your choosen hash engine
    char mdString[41] = {'\0'};
    for(int i = 0; i < 20; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("HMAC digest: %s\n", mdString);
 
    return 0;
}
