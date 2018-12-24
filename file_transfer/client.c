#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "client_func.h"
#include "defines.h"

int main()
{
    struct sockaddr_in serv_addr;
    int soc;
    int c;
	//recieve string
	char recv_buf[17];
	recv_buf[16] = (char)NULL;

	char file_buf[BUFSIZE+1];

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7500);	//port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Client test \n");
	printf("wait data... \n");
	
	soc = client_create(serv_addr);
	
	client_send_file("pic.jpg", file_buf, BUFSIZE, soc);

	c = recv(soc, recv_buf, 16, 0);
	if(c <= 0)
	{
		perror("recv request error");
	}
	else printf("RECIEVED DATA: %s\n", recv_buf);
}
