#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 10000

int main(int argc, char *argv[]){
  int source;
  int destination;
  int input;
  char buffer[BUFFER_SIZE];
  struct stat attributes;

  if(argc != 3){
    exit (1);
  }
  source = open(argv[1], O_RDONLY);
  if(source < 0){
    exit(2);
  }
  stat(argv[2], &attributes);

  if(S_ISREG(attributes.st_mode)){
    destination = open(argv[2], O_RDWR);
    if(destination < 0){
      exit(2);
    }
  }
  else{
    destination = creat(argv[2], O_RDWR);
    if(destination < 0){
      exit(3);
    }
  }

  while(1){
    input = read(source, buffer, BUFFER_SIZE);
    if(input <= 0){
      break;
    }

    input = write(destination, buffer, input);
    if(input <= 0){
      break;
    }
  }

  close(source);
  close(destination);
  exit(0);
}