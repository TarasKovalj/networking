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
    int soc1, soc2, soc3;
	int soc[N];
	int c1,c2;
	char recv_buf[BUFSIZE+1];
	char send_buf[BUFSIZE+1];
	
	struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(7500);	//port
    local.sin_addr.s_addr = htonl(INADDR_ANY);
	
	struct sockaddr_in local2;
    local2.sin_family = AF_INET;
    local2.sin_port = htons(7501);	//port
    local2.sin_addr.s_addr = htonl(INADDR_ANY);
	
	struct sockaddr_in local3;
    local3.sin_family = AF_INET;
    local3.sin_port = htons(7502);	//port
    local3.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Server test \n");
	printf("wait data... \n");
	
	pthread_t thread1, thread2, thread3;	// thread struct
	int tret1, tret2, tret3;							// thread return
	
	void *thread1_func(void)
	{
		soc1 = server_create(local);
		
		int cr1, cs1;
		while(1)
		{
			do {
				cr1 = recv(soc1, recv_buf, BUFSIZE, 0);
				if ( cr1 > 0 ) {
					printf("%s\n", recv_buf);
					cs1 = send(soc1, recv_buf, BUFSIZE, 0);
					cs1 = send(soc2, recv_buf, BUFSIZE, 0);
					cs1 = send(soc3, recv_buf, BUFSIZE, 0);
				}
				else if ( cr1 == 0 )
					cr1 = 0;//printf("connection1 closed\n");
				else
					printf("recv1 error\n");
			} while ( cr1 > 0 );
			
			sleep(1);
		}
	}
		
	void *thread2_func(void)
	{
		soc2 = server_create(local2);
		
		int cr2, cs2;
		while(1)
		{
			do {
				int cr2 = recv(soc2, recv_buf, BUFSIZE, 0);
				if ( cr2 > 0 ) {
					printf("%s\n", recv_buf);
					cs2 = send(soc1, recv_buf, BUFSIZE, 0);
					cs2 = send(soc2, recv_buf, BUFSIZE, 0);
					cs2 = send(soc3, recv_buf, BUFSIZE, 0);
				}
				else if ( cr2 == 0 )
					cr2 = 0;//printf("connection2 closed\n");
				else
					printf("recv2 error\n");
			} while ( cr2 > 0 );
			
			sleep(1);
		}
	}
	
	void *thread3_func(void)
	{
		soc3 = server_create(local3);
		
		int cr3, cs3;
		while(1)
		{
			do {
				int cr3 = recv(soc3, recv_buf, BUFSIZE, 0);
				if ( cr3 > 0 ) {
					printf("%s\n", recv_buf);
					cs3 = send(soc1, recv_buf, BUFSIZE, 0);
					cs3 = send(soc2, recv_buf, BUFSIZE, 0);
					cs3 = send(soc3, recv_buf, BUFSIZE, 0);
				}
				else if ( cr3 == 0 )
					cr3 = 0;//printf("connection2 closed\n");
				else
					printf("recv2 error\n");
			} while ( cr3 > 0 );
			
			sleep(1);
		}
	}
	
	tret1 = pthread_create(&thread1, NULL, (void *)thread1_func, NULL);
	tret2 = pthread_create(&thread2, NULL, (void *)thread2_func, NULL);
	tret3 = pthread_create(&thread3, NULL, (void *)thread3_func, NULL);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	pthread_join( thread3, NULL);

	//close(soc1);
}
