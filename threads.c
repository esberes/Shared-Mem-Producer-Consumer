#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include "queue.h"

#define BUFFSIZE 4096

/*
 * reads the information from standard input then adding it to a queue of character strings 
 * takes information from the queues that were passed from main 
 *
 * @param void *queues 
 * @return void
 * @authors libby howard and ellie beres
 */
void *readText(void *queues){

        Queue **queue = (Queue **) queues;

        // characters will be written to "str"
        char *str = malloc(BUFFSIZE * sizeof(char));
        if(str == NULL) {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(1);
        }

        int counter = 0;
        int check = 0;
        char c;

        // loop through input until end of file
        while((c = getc(stdin)) != EOF) {

                // if line exceeds size of buffer, flush it 
                if(counter >= BUFFSIZE) {
                        str[counter - 1] = '\0';
                        // need to read in rest of error line in order to start
                        // at next new line
                        while(c != '\n' && c != EOF) {
                                c = getc(stdin);
                        }
                        fprintf(stderr, "Error: the size of this line is greater than buffer size\n");
                        counter = 0;
                        free(str);
                        str = malloc(BUFFSIZE * sizeof(char));
                        continue;
                }


                // add current char to str 
                if (c != '\n') {
                        str[counter++] = (char) c;
                }

		else {
			
			str[counter] = '\0';

                        // add complete string to queue
                        EnqueueString(queue[0], str);
                        check = 1;

                        // reset counter and str
                        counter = 0;
                        str = malloc(BUFFSIZE * sizeof(char));
                        if(str == NULL) {
                                fprintf(stderr, "Failed to allocate memory\n");
                                exit(1);
                        }
                }
        }
	
	// if no new line character after string
        if (c == EOF && check == 0) {
                EnqueueString(queue[0], str);
        }

        EnqueueString(queue[0], NULL);
        pthread_exit(NULL);
}

/*
 * scans lines from queues paramater and converts lower case characters into uppercase characters
 * pass another queue of character strings to writer
 *
 * @param void *queues
 * @return void
 * @authors libby howard and ellie beres
 */
void *munch2(void *queues) {

        Queue **queue = (Queue **) queues;

        // string that we will parse 
        char *str = DequeueString(queue[1]);

        // loop until there is a null string 
        while (str != NULL) {

                int counter = 0;

                // looping until end of str
                while (str[counter] != '\0') {

                        // convert lower case letters to upper case
                        if(islower(str[counter])) {
                                str[counter] =toupper(str[counter]);
                        }
                        counter++;
                }

                // adding string to the next queue 
                EnqueueString(queue[2], str);

                // movingn to next string 
                str = DequeueString(queue[1]);
        }

        EnqueueString(queue[2], NULL);
        pthread_exit(NULL);

}

/*
 * reads information from the queues paramater
 * changes a space character to a * character 
 * passes a queue of character strings to munch2 
 *
 * @param void *queues
 * @return void 
 * @authors libby howard and ellie beres
 */
void *munch1(void *queues){

        Queue **queue = (Queue **) queues;

        // string that we will parse
        char *str = DequeueString(queue[0]);

        // loop until there is a null string
        while(str != NULL){

                int counter = 0;

                // looping to find the spaces
                while(str[counter] != '\0') {

                        // checking if the character is a space, change to * if true
                        if(str[counter] == ' '){
                                str[counter] = '*';
                        }
                        counter += 1;
                }

                // adding string to the next queue
                EnqueueString(queue[1], str);

                // moving to next string
                str = DequeueString(queue[0]);
        }

        EnqueueString(queue[1], NULL);
        pthread_exit(NULL);
}

/*
 * scans text from the queues paramater and then prints it using standard out
 *
 * @param void *queues
 * @return void
 * @authors libby howard and ellie beres
 */
void *writeText(void *queues){

        Queue **queue = (Queue **) queues;

        char *str = DequeueString(queue[2]);
        long counter = 0;

        // looping until queue is empty
        while(str !=NULL) {

                //printing line from the thread
                fprintf(stdout, "%s\n", str);
                free(str);

                //dequeue to get next string
                str = DequeueString(queue[2]);

                counter++;
        }

        printf("Number of strings processed: %ld\n", counter);

        pthread_exit(NULL);
}
