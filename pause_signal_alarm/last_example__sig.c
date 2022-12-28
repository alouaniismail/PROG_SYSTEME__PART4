#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include<string.h>

int count_signal=0;

void count(int signum){
  count_signal++;
}

int main(){
  struct sigaction sa;
  sa.sa_handler=count;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  sigaction(SIGUSR1,&sa,NULL);
  while(1){
    printf("count signal=%d\n",count_signal);
    pause();
  }
}
