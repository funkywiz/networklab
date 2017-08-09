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
int csize;
memset(&clientaddr,0,sizeof(clientaddr));
clientaddr.sin_family = AF_INET;
clientaddr.sin_addr.s_addr = INADDR_ANY;
clientaddr.sin_port = htons(PORT);
csize=sizeof(client);
while(1){	
	printf("\nEnter any message to client.. :\n");
	scanf("%s",buf);
	sendto(client,buf,sizeof(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
	if(strcmp("bye",buf)==0)
break;
	recvfrom(client,buf,sizeof(buf),0,(struct sockaddr *)&clientaddr,&csize);
	printf("\nMessage from server... ");
	printf("%s",buf);
}
close(client);
return 0;

}
