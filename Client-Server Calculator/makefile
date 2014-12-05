all: Client Server

Client: math_client.o
	gcc math_client.o -o Client

Server: math_server.o
	gcc math_server.o -o Server

math_client.o: math_client.c local_sock.h
	gcc -c math_client.c -g

math_server.o: math_server.c local_sock.h
	gcc -c math_server.c -g

.PHONY: clean
clean:
	rm math_client.o math_server.o Server Client
