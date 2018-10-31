#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 999999999

#include <sys/stat.h>
//get file size
int file_size(char *filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;
    printf("the size of file %s is : %d byte\n", filename, size);
    return size;
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

//inputName: 1.txt  -> outputName:1.txt.txt
void initOutname(char *filename)
{
    int nameLen = strlen(filename), suffixLen = 0;
    char *first = strrchr(filename, '.');
    if (first == NULL) return ;
    strcat(filename, first);
}

int main(int argc, char *argv[])
{
    char *buffer = NULL;
    char filename[100] = "1.txt";
    char txt[] = ".txt";
    int len = file_size(filename);

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("%s: can not open %s\n", __func__, filename);
        return -1;
    }

    long llen = file_size2(file);

    //len bytes
    buffer = malloc(len);
    // printf("%ld\n", sizeof(char));
    if(NULL != buffer)
    {
        printf("success\n");
    }
    else
    {
        printf("the file is too large to load!\n");
        return -1;
    }
    /* 将文件拷贝到buffer中 */
    size_t result = fread (buffer, 1, llen, file);

    if (result != llen)
    {
        return -1;
    }
    printf("%ld\n", result);
    printf("%s\n", buffer);

    initOutname(filename);
    FILE *fileOut = fopen(filename, "w+");
    if (!fileOut)
    {
        printf("%s: can not open %s\n", __func__, filename);
        return -1;
    }
    result = fwrite(buffer, 1, llen, fileOut);
    if (result != llen)
    {
        printf("%s: can not write %s\n", __func__, filename);
        return -1;
    }

    fclose (fileOut);
    fclose (file);
    free(buffer);
    return 0;
}