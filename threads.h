/** @file threads.h
 * 
 * @authors Libby Howard and Ellie Beres  
 *
 */

#ifndef THREADS_H
#define THREADS_H

void *readText(void *queues);

void *munch1(void *queues);

void *munch2(void *queues);

void *writeText(void *queues);

#endif /* THREADS_H */

/*** end of file ***/
