#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "defines.h"

int client_create(struct sockaddr_in serv_addr)
{
	int soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc < 0)
    {
        perror("socket request error");
    }

    int c = connect(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(c)
    {
        perror("connect request error");
    }
	return soc;
}

void client_send_file(char * file_name, char * buffer, char buffer_size, int socket)
{
	int c;
	FILE * pfile = fopen(file_name, "r");
	if (pfile!=NULL)
	{
		while ( feof(pfile)==0 )
		{
			int readres = fread(buffer, 1, buffer_size, pfile);
			buffer[buffer_size] = readres;
			//printf("read %d bytes from file\n", readres);
			c = send(socket, buffer, buffer_size+1, 0);	//parameter - Socket, buffer, buffer lenght, flags
			if(c <= 0)
			{
				perror("Send request error");
			}
		}
		buffer[buffer_size] = EOF_code;
		c = send(socket, buffer, buffer_size+1, 0);
		if(c <= 0)
		{
			perror("Send request error");
		}
	}
	else printf("file open error");
}
