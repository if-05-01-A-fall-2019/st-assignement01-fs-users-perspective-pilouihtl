#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

const char* getType(struct stat attributes){
  if(S_ISREG(attributes.st_mode)){
    return "Regular File";
  }
  if(S_ISDIR(attributes.st_mode)){
      return "Directory";
  }
  if(S_ISCHR(attributes.st_mode)) {
      return "Character device";
  }
  if(S_ISBLK(attributes.st_mode)){
      return "Block device";
  }
  if(S_ISFIFO(attributes.st_mode)){
      return "FIFO";
  }
  if(S_ISLNK(attributes.st_mode)){
    return "symlink";
  }
  return "Not Found";
}

int main(int argc, char const *argv[]) {
  struct stat attributes;

  if(stat(argv[1], &attributes) == 0){
    printf("------------------------ %s --------------------\n", argv[1]);
    printf("File type                : %s\n", getType(attributes));
    printf("Access privileges        : ");
    printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
    printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
    printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
    printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("inode-Number             : %ld\n",(long) attributes.st_ino);
    printf("Device Numbers           : %ld\n", attributes.st_dev);
    printf("Link count               : %ld\n",(long) attributes.st_nlink);
    printf("UID                      : %ld\n",(long) attributes.st_uid);
    printf("GID                      : %ld\n",(long) attributes.st_gid);
    printf("File size                : %ld\n",(long) attributes.st_size);
    printf("Last access              : %s",ctime(&attributes.st_atime));
    printf("Last modification        : %s",ctime(&attributes.st_mtime));
    printf("Last inode change        : %s",ctime(&attributes.st_ctime));
  }

  else{
    printf("File '%s' does not exist.\n", argv[1]);
  }

  return 0;
}
