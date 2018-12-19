all: ccomp clink

client: client.c
	gcc -o client client.c -lws2_32
server: server.c
	gcc -o server server.c -lws2_32
ccomp: 
	gcc -c client.c -lws2_32
clink:
	gcc -o client client.o -lws2_32
scomp: 
	gcc -c server.c -lws2_32
slink:
	gcc -o server server.o -lws2_32

clean:
	rm -rf *.o