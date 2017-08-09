#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5053

int main(int argc , char *argv[])
{
	int i,len,num,rc;
	int server,client;
	int buffer[3];
	int answer[1];
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	num= atoi(argv[1]);
	server=socket(AF_INET, SOCK_STREAM, 0);
	printf("ISERVER SOCKET  CREATED \n");
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	rc = bind(server, (struct sockaddr *)&addr, sizeof(addr));
	if(rc < 0)
	{
		perror("Iserver - bind() error");
		close(server);
		exit(-1);
	}
	else
		printf("Iserver - bind() is OK\n");
	printf("Binding done...\n");
	listen(server,5);
	printf("SERVER IS WAITING FOR CLIENT\n");
	for(i=0;i<1;i++){
		printf("CLIENT CONNECTING \n");
		printf("CLIENT CONNECTED\n");
		client= accept(server,NULL,NULL);
		//printf("\n GET() is OK and successful\n");
		recv(client,buffer,sizeof(buffer),0);
		printf("\n GET() is OK and successful\n");
		printf("Message from the client is %d %d\n",buffer[0],buffer[1]);
		printf("POSTING to client ..");
		answer[0]=buffer[0]*buffer[1];
		printf("POSTED VALUE- is %d",answer[0]);
		send(client,answer,sizeof(answer),0);
		printf("\n ISERVER POSTING is done\n");
		close(client);

	}
	close(server);
	return 0;
}
