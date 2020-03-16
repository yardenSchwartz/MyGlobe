Globe: Countries.o HashTable.o KeyValuePair.o LinkedList.o main.o
	gcc Countries.o HashTable.o KeyValuePair.o LinkedList.o main.o -o Globe

Countries.o: Countries.c Countries.h Defs.h
	gcc -c Countries.c

HashTable.o: HashTable.c KeyValuePair.h Defs.h LinkedList.h HashTable.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

main.o: main.c Countries.h Defs.h KeyValuePair.h LinkedList.h HashTable.h
	gcc -c main.c

clean: 
	rm *.o Globe
