/** @file stats.h
 * 
 * @author Ellie Beres 
 *
 */ 

#ifndef STATS_H
#define STATS_H
#include <semaphore.h>

typedef struct Statistics {
	int enqueueCount;
	int dequeueCount; 
	double enqueueTime;
	double dequeueTime;
	sem_t enqueueLock;
        sem_t dequeueLock; 	
} Statistics;

Statistics *InitStats();

void UpdateEnqueueStats(Statistics *stats, double startTime, double endTime);

void UpdateDequeueStats(Statistics *stats, double startTime, double endTime);

void PrintStats(Statistics *stats);


#endif /* STATS_H */

/*** end of file ***/
