thread: thread.o
	gcc thread.o -lpthread -o thread

thread.o: thread.c
	gcc -c thread.c -g

.PHONY: clean
clean:
	rm thread.o thread
