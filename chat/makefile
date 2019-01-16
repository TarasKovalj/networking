all: clean chat

chat: clean cc cs cht

cc:
	gcc -o chat_client chat_client.c client_func.c -pthread
cs: server_func.c server_func.h
	gcc -o chat_server chat_server.c server_func.c -pthread
cht:
	gcc -o cht cht.c server_func.c -pthread

clean:
	rm -rf *.o