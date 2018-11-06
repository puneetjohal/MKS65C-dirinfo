#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>


//    printf("Errors:%s\012", strerror(errno));

//converts the octal result of mode into -rw-r--r-- <- or something
void modeConvert(int mode){
  //used temporal contionals to make
  printf( (S_ISDIR(mode)) ? "d" : "-");
  //& is bitwise operator to compare similar numbers in binary
  //if mode is the same as second value return the proper letter
  printf( (mode & S_IRUSR) ? "r" : "-");
  printf( (mode & S_IWUSR) ? "w" : "-");
  printf( (mode & S_IXUSR) ? "x" : "-");
  printf( (mode & S_IRGRP) ? "r" : "-");
  printf( (mode & S_IWGRP) ? "w" : "-");
  printf( (mode & S_IXGRP) ? "x" : "-");
  printf( (mode & S_IROTH) ? "r" : "-");
  printf( (mode & S_IWOTH) ? "w" : "-");
  printf( (mode & S_IXOTH) ? "x" : "-");
}

//size converter
void sizeConvert(long byt){
  if (byt > 1000000000){
    printf("%lf gigabytes\012", (float)byt/1000000000);
  }
  else if (byt > 1000000){
    printf("%lf megabytes\012", (float)byt/1000000);
  }
  else if (byt > 1000){
    printf("%lf kilobytes\012", (float)byt/1000);
  }
  else {
    printf("%ld bytes\012", byt);
  }
}

//Permission, UserID, GroupID, Time, Mode
void showInfo(char * file){
  struct stat * buff = malloc(sizeof(struct stat));
  int s = stat(file, buff);
  if(s<0){
    printf("    Errors:%s\012", strerror(errno));
  }
  struct passwd * pass = malloc(sizeof(struct passwd));
  char date[36];
  strftime(date, 36, "%c", localtime(&(buff->st_atime)));
  modeConvert(buff->st_mode);
  pass = getpwuid(buff->st_uid);
  printf(" %s ", (pass->pw_name));
  pass = getpwuid(buff->st_gid);
  // printf("%s ", (pass->pw_name));
  printf("%s ",date);
  sizeConvert(buff->st_size);

}


//lists all the files in directory
void listFiles(char * path){
  DIR * d;
  d = opendir(path);
  //printf("OPENED\012");
  struct dirent * entry;
  entry = readdir(d);
  while (entry){
    if (entry->d_type == DT_DIR){
      printf("%s \104irectory: %s\012", path ,entry->d_name);

      //Recursive portion for sub direcories
      // if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0){
      //   listFiles(entry->d_name);
      // }

    }
    else {
      printf("File: %s\012", entry->d_name);
      showInfo(entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);
}

//show the total size of all the regular files the directory
int fileSize(char * file){
  DIR * d;
  d = opendir(file);
  //printf("OPENED\012");
  struct dirent * entry;
  int size = 0;
  struct stat * buff = malloc(sizeof(struct stat));
  entry = readdir(d);
  while (entry){
    stat(entry->d_name, buff);
    if (entry->d_type != DT_DIR){

      //printf("File: %s\012", entry->d_name);
      //printf("Size: %lld\012", buff->st_size);
      size += buff->st_size;
    }
    entry = readdir(d);
  }
  closedir(d);
  printf("Total size: %d\012", size);
  return size;
}

int main(int argc, char * argv[]){
  printf("%d\n", argc);
  printf("%s\n", argv[0]);
  // char buf[100];
  // fgets(buf, 100, stdin);
  // printf("%s\n", buf);
  printf("List of Items in Directory:\012");
  listFiles("./");
  fileSize("./");
  return 0;
}
