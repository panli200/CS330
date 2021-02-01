/***********************************************************
 * Li Pan CS330 Lab10 Signal
 * Question 1 Answer:
 * 1
 * exit SIGINT
 * core SIGQUIT
 * stop SIGTSTP
 * ignore SIGCHLD
 * 2
 * SIGKILL and SIGSTOP cannot change the default action.
***********************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

static void intHandler (int signalNo, siginfo_t *info, void *context)
{
    printf ("\nSignal received %d \n", signalNo);
    if(signalNo == SIGTRAP)
    {
        printf("\nChild received signal\n");
        exit (2);
    }
    if(signalNo == SIGCHLD)
    {
        printf("\nParent received signal\n");
        exit (2);
    }
}

int main (int argc, char *argv[])
{     
    pid_t pid;
    pid = fork();   //process control  

    //Variables needed for signals
    sigset_t interruptMask;             
    struct sigaction act;

    if (pid < 0)
    {
        fprintf (stderr, "fork failed\n");
        exit (1);
    }

    if (pid == 0)    //in child process
    {
       //set the stage (the bitmask)
        sigemptyset (&interruptMask);
        sigaddset (&interruptMask, SIGTRAP);  


       //Hook up the signalhandler to SIGTRAP 
        act.sa_sigaction = &intHandler;
        act.sa_flags = SA_SIGINFO;
        sigemptyset (&(act.sa_mask));
        if (sigaction (SIGTRAP, &act, NULL) == -1)
        {
            perror ("sigaction cannot set SIGTRAP");
            exit (SIGTRAP);
        }
        while (1)
            printf ("child waiting\n");
    }
        
    if (pid > 0)   //in parent process
    {
        //set the stage (the bitmask)
        sigemptyset (&interruptMask);
        sigaddset (&interruptMask, SIGCHLD);  

        //Hook up the signalhandler to SIGCHLD 
        act.sa_sigaction = &intHandler;
        act.sa_flags = SA_SIGINFO;
        sigemptyset (&(act.sa_mask));

        if (sigaction (SIGCHLD, &act, NULL) == -1)
        {
            perror ("sigaction cannot set SIGCHLD");
            exit (SIGCHLD);
        }
            
        nanosleep((const struct timespec[]){{0, 500000L}}, NULL);
        kill (pid, SIGTRAP);    //send a SIGTRAP to the child
        while (1)
            printf ("parent waiting\n");
    }

    exit (0);
}
