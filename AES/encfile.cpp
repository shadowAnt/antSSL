
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#include "openssl/aes.h"
#pragma comment(lib,"libeay32.lib")
#define MAX_BUFFER (10*1024*1024)
unsigned char *inBuffer = (unsigned char *)malloc(MAX_BUFFER *sizeof(unsigned char));
unsigned char *outBuffer = (unsigned char *)malloc(MAX_BUFFER *sizeof(unsigned char));
AES_KEY encKey, decKey;

//fin points the file to be encrypted during the encryption phase,
//and it points the file to be decrypted during the decryption phase.
FILE *fin = nullptr;
//fout points the result of encryption and decryption.
FILE *fout = nullptr;
//the name of the file which pointed by the fout
char outFileName[1024] = {0};

/**
 * 1.txt -> 1.txt.aes_enc -> 1.aes_enc.txt
 * @name the name of file to be processed
 * @option dec or enc, their names are different
 * @return -1 is error
 */
int initFile(char *name, char *option)
{
    //open the input file
    fin = fopen(name, "rb");
    if(fin == nullptr)
    {
        printf("open file error!\n");
        return -1;
    }
    else printf("open success!\n");
    //open the output file
    if(strcmp(option, "enc") == 0)
    {
        strcpy(outFileName, name);
        strcat(outFileName, ".aes_enc");
    }
    else if(strcmp(option, "dec") == 0)
    {
        int nameLen = strlen(name), suffixLen = 0;
        char temp[512] = {'\0'};
        strncpy(temp, name, nameLen - strlen(".aes_enc"));
        char *first = strrchr(temp, '.');
        suffixLen = strlen(first);
        strncpy(outFileName, temp, strlen(temp) - suffixLen);
        strcat(outFileName, ".aes_dec");
        strcat(outFileName, first);
    }
    fout = fopen(outFileName, "wb");
    if(fout == nullptr)
    {
        printf("open file error!\n");
        return -1;
    }
    printf("%scyption:  %s to %s\n", option, name, outFileName);
    return 1;
}

/**init key
 * @param user's password
 * @param the len of password
 */
void initKey(char *pw, int pwLen)
{
    int len, i;
    // 准备32字节(256位)的AES密码字节
    unsigned char aes_keybuf[32];
    memset(aes_keybuf, 0x90, 32);
    if(pwLen < 32) len = pwLen;
    else len = 32;
    for(i = 0; i < len; i++) aes_keybuf[i] = pw[i];

    //Expand the cipher key into the encryption key schedule.
    AES_set_encrypt_key(aes_keybuf, 256, &encKey);
    AES_set_decrypt_key(aes_keybuf, 256, &decKey);
    printf("init key success!\n");
}

/**
 * [encrypt description]
 * @param  plainData    [description]
 * @param  plainDataLen [description]
 * @param  cipherData   [description]
 * @param  last         [description]
 * @return              [description]
 */
int encrypt(unsigned char *plainData, int plainDataLen, unsigned char *cipherData, bool last)
{
    int i;
    unsigned char buf[16];
    int cipherDataLen = plainDataLen - plainDataLen % 16;
    // 输入字节串分组成16字节的块
    for(i = 0; i < plainDataLen - plainDataLen % 16; i += 16)
    {
        AES_encrypt(plainData + i, cipherData + i, &encKey);
    }
    if(plainDataLen % 16 != 0)
    {
        cipherDataLen += 16;
        memset(buf, 0, 16);
        memcpy(buf, plainData + (plainDataLen - plainDataLen % 16), plainDataLen % 16);
        AES_encrypt(buf, cipherData + cipherDataLen - 16, &encKey);
    }
    if(last)
    {
        memset(buf, 0, 16);
        buf[0] = 16 - plainDataLen % 16;
        AES_encrypt(buf, cipherData + cipherDataLen, &encKey);
        cipherDataLen += 16;
    }
    return cipherDataLen;
}

/**
 * [decrypt description]
 * @param  cipherData    [description]
 * @param  cipherDataLen [description]
 * @param  plainData     [description]
 * @param  last          [description]
 * @return               [description]
 */
int decrypt(unsigned char *cipherData, int cipherDataLen, unsigned char *plainData, bool last)
{
    if(cipherDataLen % 16 != 0) return -1;
    int i;
    for(i = 0; i < cipherDataLen; i += 16)
    {
        AES_decrypt(cipherData + i, plainData + i, &decKey);
    }
    if(last)
        return cipherDataLen - 16 - plainData[cipherDataLen - 16];
    else
        return cipherDataLen;
}

void encORdec(char *option)
{
    int readSize, writeSize;
    readSize = fread(inBuffer, 1, MAX_BUFFER, fin);
    if(!strcmp(option, "enc"))
    {
        printf("start to enc!\n");
        while(readSize > 0)
        {
            writeSize = encrypt(inBuffer, readSize, outBuffer, feof(fin));
            fwrite(outBuffer, 1, writeSize, fout);
            readSize = fread(inBuffer, 1, MAX_BUFFER, fin);
        }
    }
    else if(!strcmp(option, "dec"))
    {
        printf("strat to dec!\n");
        while(readSize > 0)
        {
            writeSize = decrypt(inBuffer, readSize, outBuffer, feof(fin));
            fwrite(outBuffer, 1, writeSize, fout);
            readSize = fread(inBuffer, 1, MAX_BUFFER, fin);
        }
    }
}

//clean, release space
void cleanSpace()
{
    if(fin != nullptr)fclose(fin);
    if(fout != nullptr)fclose(fout);
    if(inBuffer != nullptr)free(inBuffer);
    if(outBuffer != nullptr)free(outBuffer);
}

/**
 * [e.g. enc 1.txt abc123]
 * @param  argc [description]
 * @param  argv [argv[1]:"enc" or "dec"; argv[2]:file; argv[3]: user key]
 * @return      [ERROR is -1]
 */
int main(int argc, char *argv[])
{
    if(argc != 4 || (strcmp(argv[1], "enc") && strcmp(argv[1], "dec")))
    {
        printf("parameter ERROR!\n");
        return -1;
    }

    //open the input file
    if(!initFile(argv[2], argv[1])) return -1;

    //init key
    initKey(argv[3], strlen(argv[3]));

    //enc  or dec
    encORdec(argv[1]);

    cleanSpace();
    return 0;
}
