#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>

void rien(int sig){
}

void mysleep(unsigned int s){
  signal(SIGALRM,rien);
  alarm(s);
  pause();//attend les s secondes~ puis le signal ne fait rien d'apres rien(int)
  signal(SIGALRM,SIG_DFL);//termine le programme.
  //en fait alarm(s) lance le gestionnaire apres s secondes
  //avant SIGALARM SIG_DFL en terme de gestionnaire
  //=>ne jamais utiliser signal()/pause() !!!
  //tu fais pause() avec une certaine vision de l'execution
  //puis avec signal() tu modifies tout, c'est incorrect.
}

int main(int argc, char** argv){
  mysleep(7);
  return 0;
}
