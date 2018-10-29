#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
 
int sha1fun(const char* str, char* mdString){
	unsigned char digest[SHA_DIGEST_LENGTH];
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	SHA1_Update(&ctx, str, strlen(str));
	SHA1_Final(digest, &ctx);
	int i;
	for (i = 0; i < SHA_DIGEST_LENGTH; i++){
		sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	}
}

int main(int arge, char* argv[]) {
	const char* str = "sha test"; 
	char mdString[SHA_DIGEST_LENGTH*2+1];

 	sha1fun(str, mdString);
	printf("SHA1 digest: %s\n", mdString);
	return 0;
}
