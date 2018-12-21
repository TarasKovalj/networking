#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define BUFSIZE 256

int main()
{
    struct sockaddr_in serv_addr;
    int soc;
    int c;
	unsigned char buf [BUFSIZE+1];
	buf [BUFSIZE] = (unsigned char)NULL;
	char recv_buf[17];
	recv_buf[16] = (char)NULL;
	
	for(unsigned int i = 0; i < BUFSIZE; i++)
	{
		buf [i] = i + 32;
	}
	
	FILE * pfile;
	int readres;
	char file_buf[33];

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7500);	//port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Client test \n");
	printf("wait data... \n");
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc < 0)//soc==INVALID_SOCKET
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

	pfile = fopen("in.txt", "r");
	if (pfile!=NULL)
	{
		while ( feof(pfile)==0 )
		{
			readres = fread(file_buf, 1, 32, pfile);
			file_buf[32] = readres;
			printf("read %d bytes from file\n", readres);
			c = send(soc, file_buf, 33, 0);	//parameter - Socket, buffer, buffer lenght, flags
			if(c <= 0)
			{
				perror("Send request error");
			}
		}
	}
	else printf("file open error");

	c = recv(soc, recv_buf, 16, 0);
	if(c <= 0)
	{
		perror("recv request error");
	}
	else printf("RECIEVED DATA: %s\n", recv_buf);
}
