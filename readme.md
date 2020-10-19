In this program, we created a program that is using pthreads and synchronization. Using four threads (reader, munch1, munch2, writer). Reader will take from standard input and pass it to a thread to munch1 in a queue of character strings. Munch1 will replace the space with a '*' then pass another queue of character strings to munch2. Munch2 will make every lower case letter a capital letter and pass the queue of character strings to writer. Writer will write the lines in standard output. 

main: initiates process   

queue: implementing the synchronization queue. There are four methods. CreateStringQueue dynamically creates a new Queue with the appropriate data, it will then return a pointer to the new queue. EnqueueString will put the pointer of the string at the end of the queue, it will also block adding to the queue if there is no space. DequeueString updates the pointer from the beginning of the queue, if empty it will block until there is space, it returns the pointer that was removed. PrintQueueStats prints the statistics. 

threads: ReadText reads the thread information from standard input. One line at a time it will read the input and pass it into another munch1 in a queue of character strings.Munch1 scans the thread information and replaces every space character with *. Then it passes another queue of character strings to munch2. Munch2 scans the thread information and makes all of the lower case characters into an uppercase character. Then it passes another queue of characters to writer. WriteText writes the results from above to standard output. 

stats: holds enqueueCount, dequeueCount, enqueueTime, dequeueTime statistics that will eventually be printed.

authors: libby howard and ellie beres
