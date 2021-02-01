/***
CS330 Assignmnet#3
Li Pan
Program: This is multithreaded program that take 10 numbers from user through command line
It creates three threads that each thread determine different funtion:
Thread1 will determine the average of list of numbers.
Thread2 will determine the minimum value.
Thread3 will determine the maximum value.
The worker threads will set these values, and the parent thread will output these values.
***/

	#include <pthread.h>	//needed for create pthread
	#include <stdlib.h>
	#include <stdio.h>
	using namespace std;

 	static int numbers = 10;

	//get the average of the list of numbers
	void *avgFunction( void *vptr_value)
	{
		int *arr = (int *)vptr_value;
		int sum = 0;
		int *average = new int;
		*average = 0;
		
		for(int i=0; i<numbers; i++)
			{
				sum += arr[i];
			}
		*average = sum / numbers;		
		
		pthread_exit(average); 	//thread exit by returning averaege
	}
	//get the minimum of the list of numbers
	void *minFunction(void *vptr_value)
	{
		int *arr = (int *)vptr_value;
		int *min = new int;
		*min = arr[0];
		for(int i=1; i<numbers; i++)
			{
				if(*min>arr[i])
				{
					*min=arr[i];
				}
			}
	
		pthread_exit(min);	//thread exit by returning min

	}
	//get the maximum of the list of numbers
	void *maxFunction(void *vptr_value)
	{
		int *arr = (int *)vptr_value;
		int *max = new int;
		*max= arr[0];
				for(int i=1;i<numbers;i++)
			{
				if(*max<arr[i])
				{
					*max=arr[i];
				}
			}	
			pthread_exit(max);	//thread exit by returning max
		}

	//main funtion for create three threads and get the calculate outcome from children thread and printout under the parent thread
	int main(int argc, char *argv[])
	{
	
		pthread_t thread1, thread2, thread3;	//create three threads
		int *arr = new int[numbers];	//initial an array with 10 numbers
		void *vptr_return1, *vptr_return2, *vptr_return3;	//initial three void pointer point to thread

		printf("Please enter %d numbers : ", numbers);	//prompt user input the 10 numbers

		//user enter 10 different integers
			for(int i=0; i<numbers; i++)
			{
				scanf("%d",&arr[i]);
			}

	
		//pass different funtion to each of threads
		pthread_create( &thread1, NULL, &avgFunction, arr);
		pthread_create( &thread2, NULL, &minFunction, arr);
		pthread_create( &thread3, NULL, &maxFunction, arr);
		
		//worker threads join to the parent thread
		pthread_join(thread1, &vptr_return1); 
		pthread_join(thread2, &vptr_return2);
		pthread_join(thread3, &vptr_return3);

		//print the the averege, max and min number from the integer array input from user
		printf("\nThe Average  value is: %d\n", *(int *)vptr_return1); 
		printf("\nThe Minimum  value is: %d\n", *(int *)vptr_return2); 	
		printf("\nThe Maximum  value is: %d\n", *(int *)vptr_return3); 
			
		delete[]arr;	//free the memory for the array numbers
		delete (int *)vptr_return1,(int *)vptr_return2,(int *)vptr_return3;	//free three threads
	
		return 0;

	}
