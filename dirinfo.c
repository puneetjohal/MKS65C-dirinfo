#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

//    printf("Errors:%s\n", strerror(errno));

//lists all the files in directory
void listFiles(char * path){
  DIR * d;
  d = opendir(path);
  //printf("OPENED\n");
  struct dirent * entry;
  entry = readdir(d);
  while (entry){
    if (entry->d_type == DT_DIR){
      printf("Directory: %s\n", entry->d_name);
    }
    else {
      printf("File: %s\n", entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);
}

//show the total size of all the regular files the directory
int fileSize(char * file){
  DIR * d;
  d = opendir(file);
  //printf("OPENED\n");
  struct dirent * entry;
  int size = 0;
  struct stat * buff = malloc(sizeof(struct stat));
  entry = readdir(d);
  while (entry){
    stat(entry->d_name, buff);
    if (entry->d_type != DT_DIR){

      printf("File: %s\n", entry->d_name);
      printf("Size: %lld\n", buff->st_size);
      size += buff->st_size;
    }
    entry = readdir(d);
  }
  closedir(d);
  return size;
}

int main(){
  printf("List of Items in Directory:\n");
  listFiles("./");
  return 0;
}
