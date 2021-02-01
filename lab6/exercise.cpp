/*
Create 3 threads which share the same resource. A bufffer initially is '0'. Thread modify the buffer 24 times. 
Each time get the value the thread print their thread ID and process ID, buffer increment one each time.  
Author: Li Pan(200371281)
*/

    #include <iostream>
    #include <cstdlib>
    #include <cstdio>
    #include <pthread.h>
    #include <sys/types.h>
    #include <unistd.h>

    using namespace std;


    pthread_mutex_t output_lock;
    pthread_t buffer;

    void * say_it( void * );

    int main(int argc, char *argv[])
    {
        int num_threads = 3;
        pthread_t *thread_ids;
        void  *p_status;

        //Use unbuffered output on stdout
        setvbuf(stdout, (char *) NULL, _IONBF, 0);


        thread_ids = new pthread_t [num_threads];

        //Generate 3 threads 
        for (int i = 0; i < num_threads; i++)
        {
            int *arg = new int;
            *arg = i;
            if( pthread_create(&thread_ids[i],NULL,say_it,arg) > 0)
            {
                    perror("creating thread:");
                    return 2;
            }
        }

        // join threads and print their return values
        for (int i = 0; i < num_threads; i++)
        {
            if (pthread_join(thread_ids[i], &p_status) != 0)
            {
                perror("trouble joining thread: ");
                return 3;
            }

            cout << (char *)p_status << endl;

            delete [] (char *)p_status;
        }

        
        printf("Total buffer accesses:%d \n",buffer);

        delete [] thread_ids;
    
        return 0;
    }

    // 
    void * say_it(void *num)
    {
    
        char *msg = new char[255];  //a dynamic message array
        int *count = new int;   //initial a count for buffer
        *count = 0; //initial the count to be '0'

        while(buffer<24)
        {
          
            
            //used to get and lock access to serial (one at a time) resources
            if (pthread_mutex_lock(&output_lock) != 0)
            {
                perror("Could not lock output: ");
                exit(4);    //something horrible happened - exit whole program with error
            
            }
            
            
            //thread modify buffer each time the buffer increment  
            if(buffer<24)
            {
                printf( "TID: %X PID: %d Buffer: %c \n", pthread_self(), getpid(), buffer +'A' );
                buffer++;
                (*count)++;       
            }
            
            //used to unlock access to serial (one at a time) resources
            if (pthread_mutex_unlock(&output_lock) != 0)
            {
                perror("Could not unlock output: ");   
                exit(5);    //something horrible happened - exit whole program with error   
            }   
            nanosleep((const struct timespec[]){{0, 5000L}}, NULL); //a sleep to simulate work
        }
       
        snprintf(msg, 255, "TID: %X worked on the buffer %d times", pthread_self(), *count);

        return msg;
    }
