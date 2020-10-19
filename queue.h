/** @file queue.h
 *
 * @authors: Libby Howard and Ellie Beres 
 */ 

#ifndef QUEUE_H
#define QUEUE_H
#include <semaphore.h>
#include "stats.h"

typedef struct Queue {
	
	int front;
	int back;
	int size;
	int currSize;

	char** text;

	sem_t readyDequeue; // wait/signal for items in the queue
	sem_t readyEnqueue; // wait/signal for available space
	sem_t mutex; // locking

	Statistics *stats; // struct holding statistics 
} Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char * DequeueString(Queue *q);

void PrintQueueStats(Queue *q);

#endif /* QUEUE_H */
