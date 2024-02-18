.PHONY: all
all: generator primeCounter

generator: generator.c
	gcc -o randomGenerator generator.c

primeCounter: primeCounter.o queue.o queue.h
	gcc -o primeCounter primeCounter.o queue.o -lpthread

primeCounter.o: primeCounter.c queue.h
	gcc -c primeCounter.c

queue.o: queue.c queue.h
	gcc -c queue.c -lpthread


.PHONY: clean

clean:
	-rm *.o randomGenerator primeCounter 2>/dev/null
