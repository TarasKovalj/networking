#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "server_func.h"
#include "defines.h"
#define N 4					// number of chats

int sock[N];
pthread_t thread[N];		// thread struct
int tret[N];						// thread return
char recv_buf[BUFSIZE];
int *thread_param[N];

FILE *pFile;

void thread_func(int * parameter);

int main()
{
	// clear previous history
	pFile = fopen("history.txt", "w");
	fclose(pFile);

	// cycle thread create
	for (int z = 0; z < N; z++){
		thread_param[z] = (int *) malloc(sizeof(int));
		*thread_param[z] = z;
		tret[z] = pthread_create(&thread[z], NULL, (void *) thread_func, thread_param[z]);
	}
	// join threads
	for (int z = 0; z < N; z++){
		pthread_join( thread[z], NULL);
	}
}

	void thread_func(int * parameter)
	{
		int cr, cs;
		int i = *parameter;
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(7500 + i);	//port
		local.sin_addr.s_addr = htonl(INADDR_ANY);

		sock[i] = server_create(local);

		// send new client notification to all
		char str[BUFSIZE+1] = {"~~~NEW USER : ClientX is online"};
		str[20] = i+48;	// ClientX, X - char nunber of client
		printf("%s\n", str);
		for (unsigned char k = 0; k < N; k++) {
			cs = send(sock[k], str, BUFSIZE, 0);
		}

		// send history
		pFile = fopen("history.txt", "r");
		while (feof(pFile) == 0) {
			fgets(recv_buf, BUFSIZE, pFile);
			cs = send(sock[i], recv_buf, BUFSIZE, 0);
		}
		fclose(pFile);

		while (1)
		{
			do {
				cr = recv(sock[i], recv_buf, BUFSIZE, 0);
				if (cr > 0) {
					printf("%s\n", recv_buf);
					pFile = fopen("history.txt", "a+");
					fputc('\n', pFile);
					fputs(recv_buf, pFile);
					fclose(pFile);

					for (unsigned char k = 0; k < N; k++) {
						cs = send(sock[k], recv_buf, BUFSIZE, 0);
					}
				} else if (cr == 0) {
					cr = 0;	//printf("connection1 closed\n");
				} else {
					printf("recv%i error\n", i);
				}
			} while (cr > 0);
			//sleep(1);
		}
	}
