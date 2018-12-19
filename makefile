all: ccomp clink

client: client.c
	gcc -o client client.c
server: server.c
	gcc -o server server.c
ccomp: 
	gcc -c client.c
clink:
	gcc -o client client.o
scomp: 
	gcc -c server.c
slink:
	gcc -o server server.o

clean:
	rm -rf *.o