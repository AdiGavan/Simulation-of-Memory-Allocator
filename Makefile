#Gavan Adrian George - 314CA

build: allocator

allocator: allocator.o
	gcc -Wall allocator.o -o allocator

allocator.o: allocator.c
	gcc -Wall -c allocator.c

clean:
	rm -f *.o allocator	
