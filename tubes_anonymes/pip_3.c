#include<stdio.h>
#include<memory.h>
#include<stdlib.h> //cf; derniere inclusion
#include<unistd.h>
#include<time.h>

int main(int argc, char** argv){
  int p1[2];//C=>P
  //p1 est ouvert du cote write pour le child
  //et p2 est ouvert du cote read pour le child
  int p2[2];//P=>C
  //avant un seul pipe pour faire du transfert
  //mono-directionnel, là on a 2 pour faire du transfert
  //dans les 2 sens.
  if(pipe(p1)==-1) return 1;
  if(pipe(p2)==-1) return 1;
  int pid=fork();
  if(pid==-1) return 2;
  if(pid==0){
    //child process.
    close(p1[0]);
    close(p2[1]);
    //le pere va envoyer une donnee au fils qui va la lire
    //au debut puis la multiplier par 4 puis la renvoyer
    //au pere.
    int x;
    if(read(p2[0],&x,sizeof(x))==-1) {return 3;}
    printf("Received %d\n",x);
    x*=4;
    if(write(p1[1],&x,sizeof(x))==-1) {return 4;}
    printf("Wrote %d\n",x);
    close(p1[1]);
    close(p2[0]);
  }
  else{
    close(p1[1]);
    close(p2[0]);
    //parent process.
    //le pere va envoyer une donnee puis lire ce que le fils a envoye
    //apres.
    srand(time(NULL));
    int y=rand()%10;
    if(write(p2[1],&y,sizeof(y))==-1) return 5;
    printf("Wrote %d\n",y);
    if(read(p1[0],&y,sizeof(y))==-1) return 6;
    printf("Result is %d\n",y);
    close(p1[0]);
    close(p2[1]);
  }
  return 0;
}
    
