#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>


char * string;
void ping_sh(int s){
  printf("%s\n",string);
}

void ping(pid_t p){
  //Gestionnaire.
  signal(SIGUSR1,ping_sh);
  int i;
  for(i=0;i<10;i++){
    if(p==0){
      //Processus fils.
      kill(getppid(),SIGUSR1);
      pause();sleep(1);
    }
    else{
      //Processus pere.
      pause();sleep(1);
      kill(p,SIGUSR1);
    }
  }
}

int main(){
  pid_t p;
  p=fork();
  switch(p){
  case 0:
    string="pong";
    break;
  default:
    string="ping";
  }
  ping(p);//processus fils.
  //on a 2 processus qui vont faire la même chose soit ping(p)
  //au debut, le pere va faire(ping(p)) p ici c'est processus fils
  //avec string="ping", cela va declencher une pause(); suspension jusqu'à
  //un signal précis. L'enfant de l'autre côté va déclencher ping(p)
  //avec p=0 et string="pong", celui-là va déclencher un signal sur le père
  //qui va reprendre son execution(apres avoir afficher ping)
  //et va faire kill(p,SIGUSR1) soit declenchement d'un signal au fils
  //qui l'attendait avec pause et qui va afficher pong ainsi de suite...
  return 0;
}

//pour simuler un ping-pong rien de plus simple.
//ping(pid_t p)
//qui fait si p==0
//kill puis pause(); sleep(1) avec le getppid
//sinon pause();sleep(1) puis kill(p,SIGUSR1).

//ne jamais utiliser signal(); pause() et surtout encore sleep()
//avec des desaccords, ca pourrait emerger donner des suites dexecutions
//en couple imprédictibles...

