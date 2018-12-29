#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "server_func.h"
#include "defines.h"
#define N 3

int main()
{
	int socket[N];
	pthread_t thread[N];		// thread struct
	int tret[N];						// thread return
	char recv_buf[BUFSIZE];
	//char send_buf[BUFSIZE+1];
	
	unsigned char counter[N];
	unsigned char i = 0;
	unsigned char *global_ptr;
	
	void client_thread(void)
	{
		/* int cr, cs;
		
		struct sockaddr_in local;
		local.sin_family = AF_INET;
		local.sin_port = htons(7500 + i);	//port
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		
		socket[i] = server_create(local);
		
		while(1)
		{	
			do {
				cr = recv(socket[i], recv_buf, BUFSIZE, 0);
				if ( cr > 0 ) {
					printf("%s\n", recv_buf);
					for (unsigned char k = 0; k < N; k++)
					{
						cs = send(socket[k], recv_buf, BUFSIZE, 0);
					}
				}
				else if ( cr == 0 )
					cr = 0;//printf("connection1 closed\n"); start server_create(local)
				else
					printf("recv1 error\n");
			} while ( cr > 0 );
			
			sleep(1);
		} */
		
		unsigned int Li =i;
		
		while(1)
		{
			printf("%d\n", Li);
			Li++;
			pause(1);
		}
	}
	
	void *ret;
	
	void f1(void)
	{
		while(1)
		{
			printf("%d\n", 111);
			//pthread_join( thread[2], NULL);
			//pause(1);
			//pthread_exit(ret);
		}
	}
	
	void f2(void)
	{
		while(1)
		{
			printf("%d\n", 222);
			//pthread_join( thread[1], NULL);
			//pause(1);
			//pthread_exit(ret);
		}
	}
	
	void f3(void)
	{
		while(1)
		{
			printf("%d\n", 333);
			//pthread_join( thread[0], NULL);
			//pause(1);
			//pthread_exit(ret);
		}
	}
	
	tret[0] = pthread_create(&thread[0], NULL, f1, NULL);
	tret[1] = pthread_create(&thread[1], NULL, f2, NULL);
	tret[2] = pthread_create(&thread[2], NULL, f3, NULL);
	pthread_join( thread[0], NULL);
	pthread_join( thread[1], NULL);
	pthread_join( thread[2], NULL);
	
	//tret[0] = pthread_create(&thread[0], NULL, client_thread, NULL);
	//pthread_join( thread[0], NULL);
	
	/* while ( i < N )
	{
		tret[i] = pthread_create(&thread[i], NULL, client_thread, NULL);
		pthread_join( thread[i], NULL);
		i++;
	} */
		
}