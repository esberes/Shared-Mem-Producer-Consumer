#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include "queue.h"
#include "stats.h"

/*
 * dynamically creates a new Queue with the appropriate data
 * returns a pointer to the new queue
 *
 * @param int size
 * @return Queue
 * @authors libby howard and ellie beres
 */
Queue *CreateStringQueue(int size){
	
	// creating new queue structure 
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	
	// error check on allocation of memory
	if(queue == NULL){
		fprintf(stderr, "Failed to allocate memory\n");
        	exit(1);
	}
	
	// initializing Queue structure members
	queue->front = 0; 
	queue->back = 0; 
	queue->size = size; // may need to hard code to test
	queue->currSize = 0;

	queue->text = (char**)(malloc(sizeof(char*)*size));
	if(queue->text == NULL) {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(1);
	}

	// initialize dequeue, enqueue and lock semaphores 
	int dequeueVal = sem_init(&queue->readyDequeue,0, 0);
	if (dequeueVal != 0) {
		fprintf(stderr, "Failed to initialize semaphore\n");
                exit(1);
	}
	int enqueueVal = sem_init(&queue->readyEnqueue,0, size);
	if (enqueueVal != 0) {
                fprintf(stderr, "Failed to initialize semaphore\n");
                exit(1);
	}
	int mutexVal = sem_init(&queue->mutex,0, 1); 
	if (mutexVal != 0) {
                fprintf(stderr, "Failed to initialize semaphore\n");
                exit(1);
	}

	// initialize stats struct
	queue->stats = InitStats(); 

	return queue;
}

/*
 * put the pointer of the string at the end of the queue,
 * block adding to the queue if there is no space
 *
 * @param Queue *q
 * @param char *string
 * @return void
 * @authors libby howard and ellie beres
 */
void EnqueueString(Queue *q, char *string) {
	
	// getting start time for enqueueCount
	clock_t startTime = clock();

	// block until there is space in the queue 
	sem_wait(&q->readyEnqueue);
	sem_wait(&q->mutex);

	// updating Queue struture members
	q->text[q->back] = string;
	q->back = (q->back+1) % (q->size); // wrap around on queue
	q->currSize += 1;

	// signal semaphores
	sem_post(&q->mutex);
	sem_post(&q->readyDequeue);
	
	// getting end time for enqueueCount
	clock_t endTime = clock();
	
	// update enqueue stat variables 
	UpdateEnqueueStats(q->stats, (double)startTime, (double)endTime); 	
}

/*
 *  updates the pointer from the beginning of the queue
 *  if empty it will block until there is space, it returns the pointer that was removed
 *
 *  @param Queue *q
 *  @return char*
 *  @authors libby howard and ellie beres
 */
char *DequeueString(Queue *q){
	// getting start time for dequeueCount
        clock_t startTime = clock();

        // block until there is an item in the queue 
	sem_wait(&q->readyDequeue);
	sem_wait(&q->mutex);

	// update queue structure members 
	char *retString = q->text[q->front];
	q->front = (q->front+1) % (q->size); // wrap around on queue
	q->currSize -= 1;  	

	// signal semaphores
	sem_post(&q->mutex);
        sem_post(&q->readyEnqueue);

        // getting end time for dequeueCount
        clock_t endTime = clock();

	// update dequeue stat variables 
	UpdateDequeueStats(q->stats, (double)startTime, (double)endTime); 

	// return string 
	return retString;
}

/*
 * prints out the queue statistics
 *
 * @param Queue *q
 * @return void
 * @authors libby howard and ellie beres
 */
void PrintQueueStats(Queue *q){
	PrintStats(q->stats);
}
