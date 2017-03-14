build: hashtable.o main.o
	gcc -g -Wall hashtable.o main.o -o tema1 -lhash -L.

main.o: main.c
	gcc -g -Wall -c main.c -o main.o

hashtable.o: hashtable.c
	gcc -g -Wall -c hashtable.c -o hashtable.o

clean:
	rm *.o tema1
