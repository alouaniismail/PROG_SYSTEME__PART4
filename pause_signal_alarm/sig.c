#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include<string.h>

volatile sig_atomic_t unprocessedSig=0;



void sighandler(int signo){//de type sig_t (typedef (void)(*sig_t)(int).).//
  if(signo==SIGINT)
    unprocessedSig=1;
}


int main(void){
  printf("This is pid %d\n",getpid());
  struct sigaction act;//on initialise la structure comme ceci.
  //il faut le sa_handler ou bien le sa_sigaction
  //et le sa_mask via des fonctions
  //et enfil le sa_flags.
  act.sa_handler=&sighandler;//sa_handler
  sigfillset(&act.sa_mask);//sa_mask
  act.sa_flags=SA_RESTART;//sa_flags
  
  if(sigaction(SIGINT,&act,NULL)==-1){
    exit(EXIT_FAILURE);
  }
  while(1){
    if(unprocessedSig){
      unprocessedSig=0;
      printf("SIGINT signal occured.\n");
    }
  }
}
