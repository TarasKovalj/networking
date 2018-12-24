#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "server_func.h"
#include "defines.h"

int main()
{
    int soc1;
	int c;
	char file_buf[BUFSIZE+1];
	
	struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(7500);	//port
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Server test \n");
	printf("wait data... \n");
	
	soc1 = server_create(local);

	server_recv_file("out.jpg", file_buf, BUFSIZE, soc1);
	
	c = send(soc1, "text from server", 16, 0);
	if(c<=0)
	{
		perror("send request error");
	}
}
