#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFF_SIZE   5           /* total number of slots */
#define NP          3           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;              /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;           /* keep track of the number of full spots */
    sem_t empty;          /* keep track of the number of empty spots */
    sem_t mutex;          /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void *Producer(void *arg)
{
    int i, item, index;
    int val;

    index = *(int *)arg;

    for (i=0; i < NITERS; i++) {

        /* Produce item */
        item = i;

        /* Prepare to write item to buf */

        /* If there are no empty slots, wait */
        sem_wait(&shared.empty);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);
        shared.buf[shared.in] = item;
        shared.in = (shared.in+1)%BUFF_SIZE;
        printf("[P%d] Producing %d ...\n", index, item); fflush(stdout);
        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Increment the number of full slots */
        sem_post(&shared.full);

        /* Interleave  producer and consumer execution */
        //if (i % 2 == 1) sleep(1);
    }
    free (arg);
    return NULL;
}

void *Consumer(void *arg)
{
    /* ----Fill in the code here */
    int i, item, index;
    int val;

    index = *(int *)arg;

    for (i=0; i < NITERS; i++) {

        /* Prepare to write item to buf */

        /* If there are empty slots, wait */
        sem_wait(&shared.full);
        /* If another thread uses the buffer, wait */
        sem_wait(&shared.mutex);
        item = shared.buf[shared.out]; //assign the value back
        shared.out = (shared.out+1)%BUFF_SIZE;
        printf("- - - - -[C%d] Consuming %d ...\n", index, item); fflush(stdout);
        /* Release the buffer */
        sem_post(&shared.mutex);
        /* Decrement the number of emptry slots */
        sem_post(&shared.empty);

        /* Interleave  producer and consumer execution */
        //if (i % 2 == 1) sleep(1);
    }
    free (arg);
    return NULL;

}

int main()
{
    pthread_t *idP, *idC;
    int index;
    int *arg;
    
    /* ----Insert code here to set your in and out indices to zero */
    shared.in = 0;
    shared.out = 0;

    /* Initialize the full and empty semaphore */
    sem_init(&shared.full, 0, 0);
    sem_init(&shared.empty, 0, BUFF_SIZE);

    /* ----Insert code here to initialize mutex */
    sem_init(&shared.mutex, 0, 1);

    /* Allocate memory for idP */
    idP= (pthread_t *)malloc (NP* sizeof(pthread_t));

    /* ----Insert code here to allocate memory for idC */
    idC= (pthread_t *)malloc (NC* sizeof(pthread_t));

    /* Create NP Producers */
    for (index = 0; index < NP; index++)
    {
       arg=(int *) malloc (sizeof(int));
       *arg=index;
       /* Create a new producer */
       pthread_create(&idP[index], NULL, Producer, arg);
    }

    /* ----Insert code here to create NC consumers */
    for (index = 0; index < NC; index++)
    {
       arg=(int *) malloc (sizeof(int));
       *arg=index;
       /* Create a new producer */
       pthread_create(&idC[index], NULL, Consumer, arg);
    }

    /* "Join" NP Producers */
    for (index = 0; index < NP; index++)
    {
       if (pthread_join(idP[index], NULL))
       {
           printf("Problem joining producer thread at index %i", index);
       }
    }
    
    /* ----Insert code here to "Join" NC consumers*/
    for (index = 0; index < NC; index++)
    {
       if (pthread_join(idC[index], NULL))
       {
           printf("Problem joining producer thread at index %i", index);
       }
    }

    /* ----Insert code here to destroy the three semaphores */
     sem_destroy(&shared.full);  //destory the semaphore
     sem_destroy(&shared.empty);
     sem_destroy(&shared.mutex);
    
    pthread_exit(NULL);
}

