#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "server_func.h"
#include "defines.h"
#define N 4

int main()
{
	int socket[N];
	pthread_t thread[N];		// thread struct
	int tret[N];						// thread return
	char recv_buf[BUFSIZE];
	//char send_buf[BUFSIZE+1];
	int *thread_param1 = (int *) malloc(sizeof(int));
	int *thread_param2 = (int *) malloc(sizeof(int));
	int *thread_param3 = (int *) malloc(sizeof(int));
	int *thread_param4 = (int *) malloc(sizeof(int));
	*thread_param1 = 0;
	*thread_param2 = 1;
	*thread_param3 = 2;
	*thread_param4 = 3;
	
	//int *thread_param[N];
	
	unsigned char counter[N];
	unsigned char *global_ptr;

	void f1(int * parameter)
	{
		int cr;
		int i = *parameter;
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(7500 + i);	//port
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		
		socket[i] = server_create(local);
		printf("~~~NEW USER : Client%d is online~~~\n", i);
		
		while(1)
		{
			if (cr < 0) {
				//close(socket[i]);
				//socket[i] = server_create(local);
			}
			do {
				cr = recv(socket[i], recv_buf, BUFSIZE, 0);
				if ( cr > 0 ) {
					printf("%s\n", recv_buf);
					for (unsigned char k = 0; k < N; k++)
					{
						int cs = send(socket[k], recv_buf, BUFSIZE, 0);
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
	
	/* for (int z = 0; z < N; z++){
		thread_param[N] = (int *) malloc(sizeof(int));
		*thread_param[z] = z;
		tret[z] = pthread_create(&thread[z], NULL, (void *) f1, thread_param[z]);
	} */
	
	tret[0] = pthread_create(&thread[0], NULL, (void *) f1, thread_param1);
	tret[1] = pthread_create(&thread[1], NULL, (void *) f1, thread_param2);
	tret[2] = pthread_create(&thread[2], NULL, (void *) f1, thread_param3);
	//tret[3] = pthread_create(&thread[3], NULL, (void *) f1, thread_param4);
	pthread_join( thread[0], NULL);
	pthread_join( thread[1], NULL);
	pthread_join( thread[2], NULL);
	//pthread_join( thread[3], NULL);
	
	//tret[0] = pthread_create(&thread[0], NULL, client_thread, NULL);
	//pthread_join( thread[0], NULL);
	
	/* while ( i < N )
	{
		tret[i] = pthread_create(&thread[i], NULL, client_thread, NULL);
		pthread_join( thread[i], NULL);
		i++;
	} */
		
}