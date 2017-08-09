#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5052
int main(int argc,char argv[])
{
	int client,inp1,inp2,array[2];
	char send_buf[100];
	int recv_buf[1];
	struct sockaddr_in addr;
	client= socket(AF_INET, SOCK_STREAM, 0);
	printf("\n Client_socket is OK");
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	connect(client,(struct sockaddr*)&addr,sizeof(addr));
	printf("client connect() is OK \n");
	printf("connection established\n");
	printf("Enter any two numbers.. ");
	scanf("%d %d",&inp1,&inp2);
	array[0]=inp1;
	array[1]=inp2;
	send(client,array,sizeof(array),0);
	printf("Client send is OK\n");
	recv(client,recv_buf,sizeof(recv_buf),0);
	printf("\n message recieved is %d\n",recv_buf[0]);
	close(client);
	return 0;
}

