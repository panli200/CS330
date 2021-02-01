//original code from http://jan.netcomp.monash.edu.au/OS/l8_1.html
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //added this to the original
#include <signal.h>
#include <sys/types.h>

static void intHandler (int signalNo, siginfo_t *info, void *context)
{
       printf("Ouch - shot in the ...\n");
       exit(2);
}

int main(int argc, char *argv[])
{
       pid_t pid;

       //Variables needed for signals
       sigset_t interruptMask;             
       struct sigaction act;

       if ((pid = fork()) < 0)
       {
               fprintf (stderr, "fork failed\n");
               exit (1);
       }

       if (pid == 0)
       {
	       //set the stage (the bitmask)
               sigemptyset (&interruptMask);
               sigaddset (&interruptMask, SIGINT);  


               //Hook up the signalhandler to SIGINT 
               act.sa_sigaction = &intHandler;
               act.sa_flags = SA_SIGINFO;
               sigemptyset (&(act.sa_mask));
               if (sigaction (SIGINT, &act, NULL) == -1)
               {
                       perror ("sigaction cannot set SIGINT");
                       exit (SIGINT);
               }
               while (1)
                       printf ("Running amok!!!\n");
       }

       sleep (3);
       kill (pid, SIGINT);
       exit (0);
}
