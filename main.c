#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "queue.h"
#include "threads.h"

#define BUFFSIZE 4096
#define QUEUE_SIZE 10



/*
 * initiates the process, creating three queues and storing them in an array which will be passed into the other modules
 *
 * @return int
 *
 * authors libby howard and ellie beres
 */
int main(){
	
	// creating queues
	Queue *readerToMunch1 = CreateStringQueue(QUEUE_SIZE);  
	Queue *munch1ToMunch2 = CreateStringQueue(QUEUE_SIZE); 
	Queue *munch2ToWriter = CreateStringQueue(QUEUE_SIZE); 

	// array holding all queues, to be passed through program
	void *queueHolder[3];
	queueHolder[0] = readerToMunch1;
	queueHolder[1] = munch1ToMunch2;
	queueHolder[2] = munch2ToWriter;

	// initializing 4 pthreads
	pthread_t readerThread;
	pthread_t munch1Thread;
	pthread_t munch2Thread;
	pthread_t writerThread;

	// creating 4 pthreads 
	if(pthread_create(&readerThread, NULL, readText, queueHolder) != 0) {
		fprintf(stderr, "Failed to create thread.");
		exit(-1);	
	}	
	if(pthread_create(&munch1Thread, NULL, munch1, queueHolder) != 0) {
                fprintf(stderr, "Failed to create thread.");
                exit(-1); 
        }
	if(pthread_create(&munch2Thread, NULL, munch2, queueHolder) != 0) {
                fprintf(stderr, "Failed to create thread.");
                exit(-1);
        }
	if(pthread_create(&writerThread, NULL, writeText, queueHolder) != 0) {
                fprintf(stderr, "Failed to create thread.");
                exit(-1);
        }

	// join the threads 
	if(pthread_join(readerThread, NULL) != 0) {
		fprintf(stderr, "Failed to join thread.");
                exit(-1);
	}
	if(pthread_join(munch1Thread, NULL) != 0) {
                fprintf(stderr, "Failed to join thread.");
                exit(-1);
        }
	if(pthread_join(munch2Thread, NULL) != 0) {
                fprintf(stderr, "Failed to join thread.");
                exit(-1);
        }
	if(pthread_join(writerThread, NULL) != 0) {
                fprintf(stderr, "Failed to join thread.");
                exit(-1);
        }

	// print queue stats 
	fprintf(stderr, "Stats of reader to munch1\n");
	PrintQueueStats(readerToMunch1);
	fprintf(stderr, "Stats of munch1 to munch2\n");
        PrintQueueStats(munch1ToMunch2);
	fprintf(stderr, "Stats of munch2 to writer\n");
        PrintQueueStats(munch2ToWriter);
	
	return 0;
}
