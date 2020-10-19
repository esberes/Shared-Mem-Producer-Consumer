CC = gcc
WARNING_FLAGS = -Wall -Wextra 
EXE = prodcom
SCAN_BUILD_DIR = scan-build-out

all: main.o queue.o threads.o stats.o
	$(CC) -o $(EXE) main.o queue.o threads.o stats.o -lpthread

main.o: main.c queue.h threads.h
	$(CC) $(WARNING_FLAGS) -c main.c 

queue.o: queue.c queue.h stats.h
	$(CC) $(WARNING_FLAGS) -c queue.c

threads.o: threads.c threads.h queue.h 
	$(CC) $(WARNING_FLAGS) -c threads.c

stats.o: stats.c stats.h

clean: 
	rm -f  $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run Clang Static Analyzer 
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

# 
# View the one scan available using firefox 
#
scan-view: scan-build 
	firefox -new-window $(SCAN_BUILD_DIR) /*/index.html 
