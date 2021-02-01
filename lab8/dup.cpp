#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int outfile1, outfile2;

  outfile1= open("myfile1", O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
  outfile2= open("myfile2", O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);


  write (outfile1, "1 hello", strlen("1 hello"));
  write (outfile2, "2 hello", strlen("2 hello"));


  dup2 (outfile2, outfile1);

  write (outfile1, "1 hello", strlen("1 hello"));
  write (outfile2, "2 hello", strlen("2 hello"));

  return 0;
}
