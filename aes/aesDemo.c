#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/aes.h"

int aesEnc_str(const unsigned char* userKey_, const int bits, const char* enc_in_, char* enc_out_){
    AES_KEY aesKey_;
    fprintf(stdout, "Original message: %s\n", enc_in_);
    AES_set_encrypt_key(userKey_, bits, &aesKey_);
    // printf("init aesKey_ success!\n");
    AES_encrypt(enc_in_, enc_out_, &aesKey_);
    // printf("enc success!\n");
    return 0;
}

int aesDec_str(const unsigned char* user_key_, const int bits, const char* dec_in_, char* dec_out_){
    AES_KEY aesKey_;
    AES_set_decrypt_key(user_key_, bits, &aesKey_);
    AES_decrypt(dec_in_, dec_out_, &aesKey_);
    fprintf(stdout, "Recovered Original message: %s\n", dec_out_); 
    return 0;
}

int main(int argc, char* argv[]){
    unsigned char enc_out_[16], dec_out_[16];
    // unsigned char* enc_out_ = NULL;
    // unsigned char* dec_out_ = NULL;
    // unsigned char enc_out_[] = "";
    // unsigned char dec_out_[] = "";

    const char* userKey_ = "0123456789123456";
    const char* enc_in_ = "0123456789123456";

    aesEnc_str(userKey_, 128, enc_in_, enc_out_);
    aesDec_str(userKey_, 128, enc_out_, dec_out_);

    return 0;
}