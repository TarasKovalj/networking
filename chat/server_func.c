#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "defines.h"

int server_create(struct sockaddr_in local)
{
	int soc = socket(AF_INET, SOCK_STREAM, 0);
	if(soc<0)
	{
		perror("socket request error");
	}
		int c = bind(soc, (struct sockaddr_in*)&local, sizeof(local));
	if(c < 0)
	{
		perror("bind request error");
	}
		c = listen(soc,5);	
	if(c)
	{
		perror("Listen request error");
	}
	
	int accepted_socket = accept(soc, NULL, NULL);	
	if(accepted_socket < 0)
	{
		perror("Accept request error");
	}
	return accepted_socket;
}

void server_recv_file(char * file_name, char * buffer, char buffer_size, int accepted_socket)
{
	int c, writeres;
	char eof_flag=0;
	FILE * pfile = fopen(file_name, "w");
	if (pfile!=NULL)
	{
		printf("RECIEVED DATA: \n");
		while (eof_flag==0)
		{
			c = recv(accepted_socket, buffer, buffer_size+1, 0);
			if(c <= 0)
			{
				perror("recv request error \n");
			}
			else 
			{
				if(buffer[buffer_size]==EOF_code) eof_flag=1;
				else
				{
					//printf("%d\n", buffer[buffer_size]);
					//for (int i =0; i<buffer[buffer_size]; i++) printf("%c", buffer[i]);
					writeres = fwrite(buffer, buffer[buffer_size], 1, pfile);
				}
			}
		}
		printf("file is succsessfully recieved\n");
	}
}