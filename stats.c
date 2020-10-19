#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include "stats.h"

/*
 * Initialize synchronization variables and structure members
 *
 * @return Statistics
 */
Statistics *InitStats() {

	// create stats structure 
	Statistics *stats = (Statistics *)malloc(sizeof(Statistics));
	
	// error check on allocation of memory 
	if (stats == NULL) {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(1);
	}
        
	// initialize Stats structure members 
	stats->enqueueCount = 0;
	stats->dequeueCount = 0;
	stats->enqueueTime = 0;
	stats->dequeueTime = 0;
	int enqueueStats = sem_init(&stats->enqueueLock, 0, 1);
	if (enqueueStats != 0) {
                fprintf(stderr, "Failed to initialize semaphore\n");
                exit(1);
	}
	int dequeueStats = sem_init(&stats->dequeueLock, 0, 1); 
	if (dequeueStats != 0) {
                fprintf(stderr, "Failed to initialize semaphore\n");
                exit(1);
	}
	return stats;
} 

/*
 * Update enqueueCount and enqueueTime - only one thread allowed in at a time 
 *
 * @params stats, startTime, endTime
 */
void UpdateEnqueueStats(Statistics *stats, double startTime, double endTime) {

	sem_wait(&stats->enqueueLock); 

	// update enqueue stats 
	stats->enqueueCount++;
	stats->enqueueTime += (endTime - startTime); 

	sem_post(&stats->enqueueLock);
}

/*
 * Update dequeueCount and dequeueTime - only one thread allowed in at a time
 *
 * @params stats, startTime, endTime
 */
void UpdateDequeueStats(Statistics *stats, double startTime, double endTime) {

	sem_wait(&stats->dequeueLock); 

	// update dequeue stats 
	stats->dequeueCount++;
	stats->dequeueTime += (endTime - startTime); 

	sem_post(&stats->dequeueLock);
}

/*
 * Print queue statistics to stderr 
 *
 * @param stats 
 */
void PrintStats(Statistics *stats) {
	fprintf(stderr, "Enqueue Count: %d\n", stats->enqueueCount);
	fprintf(stderr, "Dequeue Count: %d\n", stats->dequeueCount);
	fprintf(stderr, "Enqueue Time: %lf\n", stats->enqueueTime / CLOCKS_PER_SEC);
	fprintf(stderr, "Dequeue Time: %lf\n", stats->dequeueTime / CLOCKS_PER_SEC);
}
