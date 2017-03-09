build: hashtable.o main.o
	gcc hashtable.o main.o -o tema1

main.o: main.c
	gcc -c main.c -o main.o

hashtable.o: hashtable.c
	gcc -c hashtable.c -o hashtable.o

clean:
	rm *.o tema1
