#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5052

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
	printf("ISERVER IS LISTENING...\n");
	for(i=0;i<num;i++){
		printf("ITERATION %d\n",i+1);
		printf("waiting on accept");
		client= accept(server,NULL,NULL);
		printf("\n Accept is OK and successful\n");
		recv(client,buffer,sizeof(buffer),0);
		printf("Message from the client is %d %d\n",buffer[0],buffer[1]);
		printf("Echoing answer back to client--");
		answer[0]=buffer[0]*buffer[1];
		printf(" answer is %d",answer[0]);
		send(client,answer,sizeof(answer),0);
		printf("\n ISERVER sending is done\n");
		close(client);

	}
	close(server);
	return 0;
}
