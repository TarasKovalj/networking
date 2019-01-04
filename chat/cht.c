#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "server_func.h"
#include "defines.h"
#define N 4

int sock[N];
pthread_t thread[N];		// thread struct
int tret[N];						// thread return
char recv_buf[BUFSIZE];
int *thread_param[N];


void f1(int * parameter);

int main()
{
	for (int z = 0; z < N; z++){
		thread_param[z] = (int *) malloc(sizeof(int));
		*thread_param[z] = z;
		tret[z] = pthread_create(&thread[z], NULL, (void *) f1, thread_param[z]);
	}
	
	for (int z = 0; z < N; z++){
		pthread_join( thread[z], NULL);
	}	
}

	void f1(int * parameter)
	{
		int cr;
		int i = *parameter;
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(7500 + i);	//port
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		
		sock[i] = server_create(local);
		printf("~~~NEW USER : Client%d is online~~~\n", i);
		
		while(1)
		{
			if (cr < 0) {
				//close(sock[i]);
				//sock[i] = server_create(local);
			}
			do {
				cr = recv(sock[i], recv_buf, BUFSIZE, 0);
				if ( cr > 0 ) {
					printf("%s\n", recv_buf);
					for (unsigned char k = 0; k < N; k++)
					{
						int cs = send(sock[k], recv_buf, BUFSIZE, 0);
					}
				}
				else if ( cr == 0 )
					cr = 0;//printf("connection1 closed\n"); start server_create(local)
				else
					printf("recv%i error\n", i);
			} while ( cr > 0 );
			
			sleep(1);
		}
	}
	