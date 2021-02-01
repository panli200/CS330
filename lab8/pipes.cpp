/*
Li Pan 
CS330 Lab8
Question1_Answer cat colorfile.txt | grep -v -n color > color.txt
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main (void)
{
	int f_des[2];
    //create two argument verctors
    char *myargv[]={(char *)"grep", (char *)"-o", (char *)"color", (char *)"colorfile.txt", NULL};
    char *myargv2[]={(char *)"wc", (char *)"-w", NULL};

    int outFile;

	if (pipe(f_des)==-1)
	{
		perror("Pipe");
		exit(1);
	}
	switch (fork()) 
	{
		case -1:
			perror("Fork");
			exit(2);
		case 0:		/*In the child*/
			dup2(f_des[1], fileno(stdout));
			close(f_des[0]);    //close to avoid the floating error
			close(f_des[1]);    //close to avoid the floating error
			execvp("grep",myargv);  //execute the grep command 
			exit(3);
		default:      /*In the parent*/
            outFile = open("newfile.txt", O_WRONLY | O_CREAT, S_IREAD | S_IWUSR);   //give the permission to the ourFile
			dup2(f_des[0], fileno(stdin));
			close(f_des[0]);    //close to avoid the floating error
			close(f_des[1]);    //close to avoid the floating error
            dup2(outFile, fileno(stdout));  //parent call standard output to the file
			execvp("wc",myargv2);   //execute the wc command 
			exit(4);
	}
}