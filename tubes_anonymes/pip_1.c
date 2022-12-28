#include<stdio.h>
#include<memory.h>
#include<unistd.h>


int main(int argc, char** argv){
  char buffer[BUFSIZ+1];
  int fd[2];
  pipe(fd);

  write(fd[1],"Hello World\n",strlen("Hello World\n"));
  read(fd[0],buffer,BUFSIZ);

  printf("%s\n",buffer);
}
