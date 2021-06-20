#include "file_util.h"
#include <pthread.h>

const char *filename = "";
int shift = 1;
char path[PATH_MAX] = "";

void* decrypt(void *data);

pthread_mutex_t mutex;

int main(int argc, const char *argv[]) {
  // control de args
  if(argc != 3) {
    printf("Usage: decrypt <shift> <.enc file>\n\n");
    exit(EXIT_SUCCESS);
  }

  // tomando nombre de archivo y shift
  shift = atoi(argv[1]);
  filename = argv[2];
  printf("decrypting...\n\n");

  // checkeo de extensión
  if(!check_ext(filename, ".enc")) {
    printf("error: decrypt requires a .enc file.\n\n");
    exit(EXIT_FAILURE);
  }
  
  // contando lineas
  int nLines = count_lines(filename);
  printf("- total lines in .enc file: %d\n", nLines);

  // abriendo archivo
  FILE *file = fopen(filename, "r");
  check_file(file);
  remove_ext(filename);
  printf("- filename: %s\n", filename);
  printf("- shift: %d\n",shift);

  // creando path
  strcat(path, "./");
  strcat(path, filename);
  strcat(path, ".dec");
  printf("path: %s\n", path);

  // mutex init
  if(pthread_mutex_init(&mutex, NULL) != 0) {
    printf("\nerror in mutex init.\n\n");
    exit(EXIT_FAILURE);
  }

  // creando y lanzando threads
  pthread_t thread_pool[nLines];
  int err;

  char *line = NULL;
  ssize_t read;
  size_t len;
  int i = 0;
  while((read = getline(&line, &len, file)) != -1) {
    err = pthread_create(&thread_pool[i], NULL, decrypt, line);
    if(err != 0)
      printf("\nerror in pthread_create.\n\n");

    pthread_join(thread_pool[i], NULL);

    i++;
  }

  fclose(file);

  if(line)
    free(line);

  pthread_mutex_destroy(&mutex);

  printf("\ndone.\n\n");
  exit(EXIT_SUCCESS);
}

void* decrypt(void *data) {
  pthread_mutex_lock(&mutex);
  char *line = (char*) data;
  
  for(int i = 0; i < strlen(line)-1; i++) {
    line[i] -= shift;
  }

  FILE *f = fopen(path, "a");
  if(f == NULL) {
    printf("error creating dec_ file.\n\n");
    exit(EXIT_FAILURE);
  }
  fputs(line, f);
  fclose(f);

  pthread_mutex_unlock(&mutex);
}
