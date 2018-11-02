#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

//    printf("Errors:%s\n", strerror(errno));

//lists all the files in directory
void listFiles(char * path){
  DIR * d;
  d = opendir(path);
  //printf("OPENED\n");
  struct dirent * entry;
  struct stat * buff = malloc(sizeof(struct stat));
  entry = readdir(d);
  while (entry){
    stat(entry->d_name, buff);
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

int check(char * dir){

}

//show the total size of all the regular files the directory
int fileSize(char * file){
  return 0;
}

int main(){
  printf("List of Items in Directory:\n");
  listFiles("./");
  return 0;
}
