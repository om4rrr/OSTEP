#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp = NULL;
    char *line = NULL;
    size_t lineLength = 0;  // Set to 0 to let getline handle allocation
                            
    FILE *tempFile = fopen("temp.txt","w+");
    for (int i = 1; i < argc; ++i)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            free(line);
            exit(1);
        }

        while (getline(&line, &lineLength, fp) != -1)
        {
          fprintf(tempFile, "%s", line);
        }

        fclose(fp);
    }

    rewind(tempFile); // reset the file position indicator of a file stream to the beginning of the file

    size_t count = 1;
    for (char prevChar = fgetc(tempFile), currChar; prevChar != EOF; prevChar = currChar) {
      
      currChar = fgetc(tempFile);
      if(currChar == prevChar)
      {
        count++;
      }
      else 
      {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prevChar, sizeof(char), 1, stdout);
        count = 1;
      }
    }

    fclose(tempFile);
    remove("temp.txt");
    tempFile = NULL;
    free(line);
    exit(0);
}

