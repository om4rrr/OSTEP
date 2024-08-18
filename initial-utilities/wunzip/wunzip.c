#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp = NULL;
    char ch;
    size_t runLength = 0;
                            
    for (int i = 1; i < argc; ++i)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

         while (fread(&runLength, sizeof(int), 1, fp) == 1)
         {
             fread(&ch, sizeof(char), 1, fp);

             for (int i = 0; i < runLength; ++i)
             {
                printf("%c", ch);
             }
         }

        fclose(fp);
    }

    exit(0);
}

