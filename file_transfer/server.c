#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#define BUFSIZE 256

int main()
{
    struct sockaddr_in local;
    int soc;
    int soc1;
	int c;
	static unsigned char buf [BUFSIZE+1];
	buf [BUFSIZE] = (unsigned char)NULL;
	
	FILE * pfile;
	int writeres;
	char file_buf[33];
	char j=0;
	char eof_flag=0;

    local.sin_family = AF_INET;
    local.sin_port = htons(7500);	//port
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Server test \n");
	printf("wait data... \n");
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc<0)
    {
        perror("socket request error");
        //exit(1);
    }

    c = bind(soc, (struct sockaddr*)&local, sizeof(local));
    if(c < 0)
    {
        perror("bind request error");
        //exit(1);
    }

	c = listen(soc,5);	
	if(c)
	{
		perror("Listen request error");
	}
	
	soc1 = accept(soc, NULL, NULL);	
	if(soc1 < 0)
	{
		perror("Accept request error");
	}
	
	pfile = fopen("out.txt", "w");
	if (pfile!=NULL)
	{
		while (eof_flag==0)
		{
			c = recv(soc1, file_buf, 33, 0);
			if(c <= 0)
			{
				perror("recv request error \n");
			}
			else 
			{
				//int n_of_byte = file_buf[32];
				if(j==0) printf("RECIEVED DATA: \n");
				printf("%d\n", file_buf[32]);
				for (int i =0; i<file_buf[32]; i++) printf("%c", file_buf[i]);
				writeres = fwrite(file_buf, file_buf[32], 1, pfile);
				//printf("\n");
			}
			j++;
			if(j==4) eof_flag=1;
		}
	}
		
	c = send(soc1, "text from server", 16, 0);
	if(c<=0)
	{
		perror("send request error");
	}
}
