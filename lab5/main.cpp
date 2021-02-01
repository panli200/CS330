/*
communicate between a child and a parent using a shared file that the user will specify
filename sent as a command line argument (argv[1])
read from input until typing CTRL-D
*/

#include <cstdio>
#include <cstdlib>
#include <sys/types.h>  //needed for open
#include <sys/stat.h>   //needed for open
#include <fcntl.h>   //needed for open
#include <unistd.h> //needed for close
#include <unistd.h>  //needed for read and write
#include <errno.h>   //for perror not allowed at here 
#include <sys/wait.h>   //needed for status checking

using namespace std;

int main(int argc, char *argv[])
{
   
   int outFile ;   //initial open file 
   int inFile;
   int n_char=0;
   int status;
   pid_t fork_return;// check the fork return
   char  buffer[10];

   if(argc != 2)  //if argument not include filename then it is an error
	{
      printf("Error: Not enough argument.\n");
	   return 0;
	}
   else
   {
      fork_return = fork( ); 

         /*in the child process*/     
         if (fork_return == 0)
         {
            
            outFile = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);   //open and create a file for user to Read and Write
            printf("\noutFile = %d \t errno = %d\n", outFile, errno);   //Initially outFile  -- errno is 0 by default
            

            if (outFile == -1)
            {
               exit(1);
            }

            n_char=write(1, "Write to the file:  ", 18); // display a prompt to user 
       
            while( (n_char = read(0, buffer, 10))!=0) //Use the read system call to read from standard input the file
            {
                n_char=write(outFile,buffer,n_char);
            }     

            close (outFile);
         }


          /*in the parent process*/    
         else if(fork_return > 0)
         {
            wait(&status);
            
            inFile = open(argv[1],O_RDONLY); //open the file for read

            printf("\ninFile = %d \t errno = %d\n", inFile, errno);  //check the perror status

            if (inFile == -1) //handle the error
            {
               exit(1);
            }

            printf("Read the file under Parent Process: \n");

                
            while( (n_char = read(inFile, buffer, 10))!=0)  //Use the write system call to standard output the file
            {
                n_char=write(1,buffer,n_char);
            }
                     
            close (inFile);
         }

         //for an error situation
         else
            printf("Error \n");
   }

   return 0;
}
