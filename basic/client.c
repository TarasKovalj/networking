#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
    struct sockaddr_in serv_addr;
    int soc;
    int c;
	char buf[17];
	buf[16]=(char)NULL;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7500);	//port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Client test \n");
	printf("wait data... \n");
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc<0)//soc==INVALID_SOCKET
    {
        perror("socket request error");
        //exit(1);
    }

    c = connect(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(c)
    {
        perror("connect request error");
        //exit(1);
    }

	c = send(soc, "text from client", 16, 0);	//parameter - Socket, buffer, buffer lenght, flags
	if(c<=0)
	{
		perror("Send request error");
	}

	c = recv(soc, buf, 16, 0);
	if(c<=0)
	{
		perror("recv request error");
	}
	else printf("RECIEVED DATA: %s\n", buf);
}
