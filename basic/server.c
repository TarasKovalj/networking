#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main()
{
    struct sockaddr_in local;
    int soc;
    int soc1;
	int c;
	char buf[17];
	buf[16]=(char)NULL;

    local.sin_family = AF_INET;
    local.sin_port = htons(7500);	//port
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Server test \n");
	printf("wait data... \n");
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
    if(soc<0)//soc==INVALID_SOCKET
    {
        perror("socket request error");
        //exit(1);
    }

    c = bind(soc, (struct sockaddr*)&local, sizeof(local));
    if(c<0)
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
	if(soc1<0)
	{
		perror("Accept request error");
	}

	c = recv(soc1, buf, 16, 0);
	if(c<=0)
	{
		perror("recv request error \n");
	}
	else printf("RECIEVED DATA: %s\n", buf);
	
	c = send(soc1, "text from server", 16, 0);
	if(c<=0)
	{
		perror("send request error");
	}
}
