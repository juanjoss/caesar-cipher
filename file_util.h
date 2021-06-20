#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define EMPTY_FILE 0

int count_lines(const char *);
void remove_ext(const char * filename);
void check_file(FILE *);
bool check_ext(const char *filename, const char *match);

void remove_ext(const char *filename) {
  char *end = (char *) filename + strlen(filename);

  while(end > filename && *end != '.' && *end != '\\' && *end != '/') {
    --end;
  }
  if((end > filename && *end == '.') && (*(end - 1) != '\\' && *(end - 1) != '/')) {
    *end = '\0';
  }
}

bool check_ext(const char *filename, const char *match) {
  const char *dot = strrchr(filename, '.');
  
  if(!dot || dot == filename) return false;
  
  if(strcmp(match, dot) != 0) return false; 

  return true;
}

void check_file(FILE *f) {
  if (f == NULL) {
    printf("error opening file.\n\n");
    exit(EXIT_FAILURE);
  }
}

int count_lines(const char *filename) {
  int lines = 0;
  char ch;
  
  FILE *f = fopen(filename, "r");
  check_file(f);

  while(!feof(f)) {
    ch = fgetc(f);

    if(ch == '\n') {
      lines++;
    }
  }

  fclose(f);

  if(lines == EMPTY_FILE) {
    printf("'%s' is an empty file.\n\n", filename);
    exit(EXIT_SUCCESS);
  }
  else {
    return lines;
  }
}

#endif
