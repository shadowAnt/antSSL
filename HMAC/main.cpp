#include "hmac.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char *argv[])
/*{
    if(argc < 2)
    {
        cout << "Please specify a hash algorithm!" << endl;
        return -1;
    }

    char key[] = "012345678";
    string data = "hello world";

    unsigned char *mac = NULL;
    unsigned int mac_length = 0;

    int ret = HmacEncode(argv[1], key, strlen(key), data.c_str(), data.length(), mac, mac_length);

    if(0 == ret)
    {
        cout << "Algorithm HMAC encode succeeded!" << endl;
    }
    else
    {
        cout << "Algorithm HMAC encode failed!" << endl;
        return -1;
    }

    cout << "mac length: " << mac_length << endl;
    cout << "mac:";
    for(int i = 0; i < mac_length; i++)
    {
        printf("%x", (unsigned int)mac[i]);
    }
    cout << endl;

    if(mac)
    {
        free(mac);
        //cout << "mac is freed!" << endl;
    }

    return 0;
}*/
{
    // ./hmac sha256 1.txt

    FILE *file = fopen(argv[2], "rb");
    if (!file)
    {
        printf("%s: can not open %s\n", __func__, argv[2]);
        return -1;
    }
    fseek(file, 0L, SEEK_END);
    int len;
    len = ftell(file) + 1;
    fseek(file, 0, SEEK_SET);
    char dat[32768] = {'\0'};
    fgets(dat, len, file);
    string data = dat;
    char key[] = "012345678";


    unsigned char *mac = NULL;
    unsigned int mac_length = 0;

    int ret = HmacEncode(argv[1], key, strlen(key), data.c_str(), data.length(), mac, mac_length);

    if(0 == ret)
    {
        cout << "Algorithm HMAC encode succeeded!" << endl;
    }
    else
    {
        cout << "Algorithm HMAC encode failed!" << endl;
        return -1;
    }

    cout << "mac length: " << mac_length << endl;
    cout << "mac:";
    for(int i = 0; i < mac_length; i++)
    {
        printf("%x", (unsigned int)mac[i]);
    }
    cout << endl;

    if(mac)
    {
        free(mac);
        //cout << "mac is freed!" << endl;
    }

    return 0;
}
