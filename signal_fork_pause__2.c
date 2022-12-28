#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv){
  int status;
  pid_t p;
  p=fork();
  switch(p){
  case -1: perror("fork"); exit(1);
  case 0: printf("%ld\n",(long)getpid()); pause();//attend les signaux.
    //suspend l'execution et permet a l'utilisateur d'envoyer des signaux.
  default://surveillance de l'enfant en amont.
    //même si on envoie des signaux, on peut faire kill -CONT
    //ce que veut WCONTINUED ou bien kill -STOP ce que veut
    //WUNTRACED puis execution de cette partie.
    //l'execution en tache de fond permet les bonnes choses(()).
    if(waitpid(p,&status,WUNTRACED|WCONTINUED)==-1){
      perror("waitpid");exit(1);
    }
    if(WIFEXITED(status)){
      printf("exited with value %d\n",WEXITSTATUS(status));
    }
    else if(WIFCONTINUED(status)){
      printf("continued\n");
    }
    else if(WIFSTOPPED(status)){
      printf("stopped by signal %d\n",WSTOPSIG(status));
    }
    else if(WIFSIGNALED(status)){
      printf("killed by signal %d\n",WTERMSIG(status));
    }
  }
  return 0;
}
