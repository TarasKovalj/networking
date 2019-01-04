#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "client_func.h"
#include "defines.h"

int main()
{
    struct sockaddr_in serv_addr;
    int soc;
    int c;
	char recv_buf[BUFSIZE+1];

	char send_buf[BUFSIZE+1] = {"C1: "};
	
	uint16_t port;
	printf("Please write the port number: ");
	scanf(" %i", &port);
	send_buf[1] = port + 48;//set name in string
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7500 + port);	//port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Client test \n");
	printf("wait data... \n");
	
	soc = client_create(serv_addr);
	
	pthread_t thread1, thread2;	// thread struct
	int tret1, tret2;							// thread return
	
	void thread1_func(void)
	{
		while(1)
		{
			int scan_res = scanf(" %[^\n]s", send_buf+4);
			//printf("%d\n", scan_res);
			if (scan_res)
			{
				int cs = send(soc, send_buf, BUFSIZE, 0);
				if (cs<=0)
				{
					perror("send request error");
				}
			}
			sleep(1);
		}
	}
	
	void thread2_func(void)
	{
		while(1)
		{
			int cr = recv(soc, recv_buf, BUFSIZE, 0);
			if (cr <= 0)
			{
				//perror("recv request error");
			}
			else printf("%s\n", recv_buf);
			sleep(1);
		}
	}
	
	tret1 = pthread_create(&thread1, NULL, thread1_func, NULL);
	tret2 = pthread_create(&thread2, NULL, thread2_func, NULL);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	//close(soc);
}
