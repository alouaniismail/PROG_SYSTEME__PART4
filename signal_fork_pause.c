#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
           pid_t cpid, w;
           int wstatus;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %ld\n", (long) getpid());
               if (argc == 1)
                   pause();                    /* Wait for signals */
	       //cela devrait attendre le signal.
	       //il faut faire ./a.out & pour faire les bonnes choses.
               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
		   //WUNTRACED detecte qu'un fils est arrete a cause d'un signal
		   //WCONTINUED detecte qu'un fils a repris l'execution.
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                   } else if (WIFSIGNALED(wstatus)) {
                       printf("killed by signal %d\n", WTERMSIG(wstatus));
                   } else if (WIFSTOPPED(wstatus)) {
                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                   } else if (WIFCONTINUED(wstatus)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
}
