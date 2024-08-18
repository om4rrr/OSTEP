#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  // no command-line arguments
  if(argc == 1)
  {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  FILE* fp = NULL;
  char* target = argv[1];
  char* currLine = NULL;
  size_t targetLength = 0;  // Set to 0 to let getline allocate the buffer

  // if a search term, but no file, is specified
  if(argc == 2)
  {
    while(getline(&currLine, &targetLength, stdin) != EOF)
    {
      if(strstr(currLine, target) != NULL)
      {
        printf("%s", currLine);
      }
    }

    free(currLine);
    exit(0);
  }

  for(int i = 2; i < argc; ++i)
  {
    fp = fopen(argv[i], "r");
    if(fp == NULL)
    {
      printf("wgrep: cannot open file\n");
      free(currLine);
      exit(1);
    }

    while(getline(&currLine, &targetLength, fp) != -1)
    {
      if(strstr(currLine, target) != NULL)
      {
        printf("%s", currLine);
      }
    }

    fclose(fp);
  }

  free(currLine);
  exit(0);
}

