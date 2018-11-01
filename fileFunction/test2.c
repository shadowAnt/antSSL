#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 32768

#include <sys/stat.h>

//inputName: 1.txt  -> outputName:1.txt.txt
void initOutname(char *filename)
{
    int nameLen = strlen(filename), suffixLen = 0;
    char *first = strrchr(filename, '.');
    if (first == NULL) return ;
    strcat(filename, first);
}

long file_size2(FILE *file)
{
    /* 获取文件大小 */
    fseek (file, 0, SEEK_END);
    long lSize;
    lSize = ftell (file);
    rewind (file);//point back to the begin
    printf("the size of file is : %ld byte\n",  lSize);
    return lSize;
}

int main(int argc, char *argv[])
{
    char *buffer = NULL;
    char filename[100];
    if(argc == 1)
    {
        strcpy(filename, "1.txt");
    }
    else if(argc == 2)
    {
        strcpy(filename, argv[1]);
    }
    else
    {
        printf("parameter ERROR!\n");
        return -1;
    }

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("%s: can not open %s\n", __func__, filename);
        return -1;
    }

    initOutname(filename);
    FILE *fileOut = fopen(filename, "w");
    fclose (fileOut);
    fileOut = fopen(filename, "a+");
    if (!fileOut)
    {
        printf("%s: can not open %s\n", __func__, filename);
        return -1;
    }

    buffer = malloc(MAXSIZE);
    if(NULL != buffer)
    {
        printf("success\n");
    }
    else
    {
        printf("%s the file is too large to load!\n", __func__);
        return -1;
    }
    /* 将文件拷贝到buffer中 */
    int bytes_read = 0;

    // int onceSize = MAXSIZE;
    // int len = file_size2(file);
    // for(; len > 0; len -= onceSize)
    // {
    //     if(len < MAXSIZE) onceSize = len;

    //     fread (buffer, 1, onceSize, file);
    //     fwrite(buffer, 1, onceSize, fileOut);
    // }

    while(bytes_read=fread (buffer, 1, MAXSIZE, file))
    	fwrite(buffer, 1, bytes_read, fileOut);

    fclose (fileOut);
    fclose (file);
    free(buffer);
    return 0;
}