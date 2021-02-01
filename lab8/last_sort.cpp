#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main (void)
{
	int f_des[2];

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
			close(f_des[0]);
			close(f_des[1]);
			execl("/usr/bin/last", "last", NULL);
			exit(3);
		default:      /*In the parent*/
			dup2(f_des[0], fileno(stdin));
			close(f_des[0]);
			close(f_des[1]);
			execl("/bin/sort", "sort", NULL);
			exit(4);
	}
}
			
			
