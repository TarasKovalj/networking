#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "server_func.h"
#include "defines.h"

int main()
{
    int soc1, soc2;
	int c;
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

    printf("Server test \n");
	printf("wait data... \n");
	
	soc1 = server_create(local);
	soc2 = server_create(local2);

	//server_recv_file("out.jpg", file_buf, BUFSIZE, soc1);
	//while(1)
	//{
		c = recv(soc1, recv_buf, BUFSIZE, 0);
		if(c <= 0)
		{
			perror("recv request error \n");
		}
		else
		{
			printf("%s\n", recv_buf);
			//recv_buf[0] = 'X';
		}
		
		c = send(soc1, recv_buf, BUFSIZE, 0);
		if(c<=0)
		{
			perror("send request error");
		}
		
		
		c = recv(soc2, recv_buf, BUFSIZE, 0);
		if(c <= 0)
		{
			perror("recv request error \n");
		}
		else
		{
			printf("%s\n", recv_buf);
		}
		
		c = send(soc2, recv_buf, BUFSIZE, 0);
		if(c<=0)
		{
			perror("send request error");
		}
	//}
	
	close(soc1);
}
