#include<stdio.h>
#include<memory.h>
#include<unistd.h>

int main(int argc, char** argv){
  //simuler ls | wc
  //revient a faire ce qui suit:
  //la sortie de ls dans le stdout via
  //l'entrée standard stdin de wc(ça marche comme ceci).

  int pfd[2];
  if(pipe(pfd)==-1) return 1;
  int pid;
  if((pid=fork())<0) return 2;
  //il faut garder en tête que ls | wc 2 commandes soit un seul fork
  //suffit.(cf; execlp)

  if(pid==0){
    /*child*/
    //il va executer wc.
    close(pfd[1]);//car il va lire des données.
    //il faut lui dire que son entrée standard c'est pfd[0].
    //il va lire des données depuis pfd[0].
    dup2(pfd[0],0);//ce qui va être produit par le père
    //va être l'entrée de ce processus.
    close(pfd[0]);
    execlp("wc","wc",(char*)0);
    printf("wc failed");//if execlp returns, it's an error.
    return 3;
  }

  else{
    close(pfd[0]);//car il va ecrire.
    dup2(pfd[1],1);//l'ecriture via pfd[1] se fera par la redirection
    //de ce qu'a fait ls (execlp apres) sur la sortie standard.
    close(pfd[1]);
    execlp("ls","ls",(char*)0);
    printf("ls failed");
    return 4;
  }
  return 0;
}
    
