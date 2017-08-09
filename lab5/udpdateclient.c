#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5054
int main()
{
	int client=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in clientaddr;
	char buf[1024];
	int csize,breaker,i;
	memset(&clientaddr,0,sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = INADDR_ANY;
	clientaddr.sin_port = htons(PORT);
	csize=sizeof(client);
	while(1){
		printf("\nprompting server to display date..\n");
		for(i=0;i<1000000000;i++)
		{	}	
		strcpy(buf,"/bin/date");
		sendto(client,buf,sizeof(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
		if(strcmp("bye",buf)==0)
			break;
		printf("Enter 1 to exit\n");
		scanf("%d",&breaker);	
		if(breaker==1)
		{
			printf("Connection closed\n");	
			return 0;
		}

	}
	close(client);
	return 0;

}

