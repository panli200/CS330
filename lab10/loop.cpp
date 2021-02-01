#include <stdio.h>
//#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	int i;

	for( i = 0;; ++i )
	{
		printf ("%i\n",i);
		sleep (1);
	}
}
