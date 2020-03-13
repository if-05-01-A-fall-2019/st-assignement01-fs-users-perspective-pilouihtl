#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL) return -1;

    while ((de = readdir(dr)) != NULL) {
      struct stat f;
      if(stat(de->d_name,&f) < 0) return 1;
      printf("\n");
      if(S_ISBLK(f.st_mode)) printf("b");
      else if (S_ISREG(f.st_mode)) printf("-");
      else if (S_ISDIR(f.st_mode)) printf("d");
      else if (S_ISCHR(f.st_mode)) printf("c");
      else if (S_ISLNK(f.st_mode)) printf("l");

      printf( (S_ISDIR(f.st_mode)) ? "d" : "-");
      printf( (f.st_mode & S_IRUSR) ? "r" : "-");
      printf( (f.st_mode & S_IWUSR) ? "w" : "-");
      printf( (f.st_mode & S_IXUSR) ? "x" : "-");
      printf( (f.st_mode & S_IRGRP) ? "r" : "-");
      printf( (f.st_mode & S_IWGRP) ? "w" : "-");
      printf( (f.st_mode & S_IXGRP) ? "x" : "-");
      printf( (f.st_mode & S_IROTH) ? "r" : "-");
      printf( (f.st_mode & S_IWOTH) ? "w" : "-");
      printf( (f.st_mode & S_IXOTH) ? "x" : "-");
      
      printf("%d ",f.st_uid);
      printf("%d ",f.st_gid);
      printf("%ld \t",f.st_size);
    }
  closedir(dr);
  return 0;
}