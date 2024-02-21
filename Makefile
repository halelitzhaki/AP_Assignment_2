.PHONY: all
all: generator primeCounter

generator: generator.c
	gcc -o randomGenerator -g generator.c

primeCounter: primeCounter.o queue.o queue.h
	gcc -o primeCounter -g primeCounter.o queue.o -lpthread

primeCounter.o: primeCounter.c queue.h
	gcc -c -g primeCounter.c

queue.o: queue.c queue.h
	gcc -c -g queue.c -lpthread

.PHONY: clean
clean:
	-rm *.o randomGenerator primeCounter 2>/dev/null
