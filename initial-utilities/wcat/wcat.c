#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{

  if(argc == 0)
    exit(0);

  FILE *fp = NULL;
  char buffer[BUFFER_SIZE];

  for (int i = 1; i < argc; ++i) {

      fp = fopen(argv[i], "r");
      if(fp == NULL)
      {
        printf("wcat: cannot open file\n");
        exit(1);
      }

      while(fgets(buffer, BUFFER_SIZE, fp) != NULL)
           printf("%s", buffer);

      fclose(fp);
  }

  exit(0);
}
