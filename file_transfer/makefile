all: clean ccomp clink scomp slink

client: client.c
	gcc -o client client.c
server: server.c 
	gcc -o server server.c

ccomp: 
	gcc -c client.c
clink: client_func.o
	gcc -o client client.o client_func.o

scomp: 
	gcc -c server.c
slink: server_func.o
	gcc -o server server.o server_func.o

client_func.o: client_func.c
	gcc -c client_func.c
server_func.o: server_func.c
	gcc -c server_func.c

clean:
	rm -rf *.o