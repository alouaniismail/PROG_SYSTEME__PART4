//BUFSIZ pour memory.h.

#include<stdio.h>
#include<memory.h>
#include<unistd.h>

int main(int argc, char** argv){
  int pfd[2];
  if(pipe(pfd)==-1){
    printf("pipe failed\n");
    return 1;
  }
  int pid;
  if((pid=fork())<0){
    printf("fork failed\n");
    return 2;
  }
  if(pid==0){
    //lire les données.
    char buffer[BUFSIZ];
    close(pfd[1]);
    while(read(pfd[0],buffer,BUFSIZ)!=0)
      printf("Child read : %s\n",buffer);
    close(pfd[0]);
  }
  else{
    char buffer[BUFSIZ];
    //ecrire les donnees.
    close(pfd[0]);
    strcpy(buffer,"Hello World\n");
    write(pfd[1],buffer,strlen(buffer)+1);
    close(pfd[1]);
  }
  return 0;
}
    
//mono-directionnelle.
//bi-directionnelle? -> voir pip_3.c.
