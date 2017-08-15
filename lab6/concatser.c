#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5054
void delayer()
{
	int temp;
	for(temp=0;temp<1000000000;temp++){ }
}
int main()
{
	int slen,clen,rc,temp,i,temp1,count=0;
	int server,client;
	struct sockaddr_in serversocket,clientsocket;
	char buf[1024];
	char buff[1024];
	char buffer[2][1024];
//	string str;
	memset(&serversocket, 0, sizeof(serversocket));
	memset(&clientsocket, 0, sizeof(clientsocket));
	server=socket(AF_INET, SOCK_DGRAM, 0);
	serversocket.sin_family = AF_INET;
	serversocket.sin_addr.s_addr = INADDR_ANY;
	serversocket.sin_port = htons(PORT);
	rc = bind(server, (struct sockaddr *)&serversocket, sizeof(serversocket));
	if(rc < 0)
	{
		perror("server error\n");
		close(server);
		exit(-1);
	}
	else
		printf("server is fine\n");
	clen=sizeof(clientsocket);
	do
	{
		while(1)
		{
			printf(" \n\n\n    MENU\n1-concatenation\n2.Size of a string\n3.Addition\n4.Subtraction\n5.exit\n6.Display answer\n");
			recvfrom(server,buf,sizeof(buf),0,(struct sockaddr*)&clientsocket,&clen);	
			if(strcmp(buf,"1\n")==0)
			{
				printf("\n||Concatenation||\nEnter two String to concatenate\n");
	                        recvfrom(server,buffer[0],sizeof(buffer[0]),0,(struct sockaddr*)&clientsocket,&clen);
				recvfrom(server,buffer[1],sizeof(buffer[0]),0,(struct sockaddr*)&clientsocket,&clen);
				printf("Entered string are %s and %s\n",buffer[0],buffer[1]);
				printf("Concatentinated string is--  ");
				i=0;
				count=0;
				 while(buffer[0][i]!='\n')
                                {
					buff[count]=buffer[0][i];
                                        i++;
					count++;
                                }
				 i=0;
                                 while(buffer[1][i]!='\n')
                                {
					buff[count]=buffer[1][i];
                                        i++;
					count++;
                                }
				delayer();
				printf("%s",buff);
			}
			else if(strcmp(buf,"2\n")==0)
			{
				printf("\n||Size of a string||\nEnter any string\n");
				recvfrom(server,buf,sizeof(buf),0,(struct sockaddr*)&clientsocket,&clen);
				i=0;
				while(buf[i]!='\n')
				{
					printf("%c",buf[i]);
					i++;
				}
				printf("Total size of data recieved is %d", i);
		        	delayer();
			}
			else if(strcmp(buf,"3\n")==0)
			{
				printf("\n||ADDITION||\nEnter two numbers\n");
				recvfrom(server,buffer[0],sizeof(buffer[0]),0,(struct sockaddr*)&clientsocket,&clen);
				recvfrom(server,buffer[1],sizeof(buffer[1]),0,(struct sockaddr*)&clientsocket,&clen);
				temp=atoi(buffer[0]);
				temp1=atoi(buffer[1]);
				printf("The sum of the two numbers is-- %d \n",temp+temp1);		
				delayer();
			}
			else if(strcmp(buf,"4\n")==0)
			{
				printf("\n||SUBTRACTION||\nEnter two numbers\n");
                                recvfrom(server,buffer[0],sizeof(buffer[0]),0,(struct sockaddr*)&clientsocket,&clen);
                                recvfrom(server,buffer[1],sizeof(buffer[1]),0,(struct sockaddr*)&clientsocket,&clen);
                                temp=atoi(buffer[0]);
                                temp1=atoi(buffer[1]);
                                printf("The Difference of the two numbers is-- %d \n",temp-temp1);
                                delayer();

			}
			else if(strcmp(buf,"5\n")==0)
			{
				printf("Exiting program");
				return 0;
			}
			else if(strcmp(buf,"6")==0)
			{
				if(strlen(buff))
				{
					strcpy(buf,buff);
					sendto(server,buf,sizeof(buf),0,(struct sockaddr*)&clientsocket,clen);
				}		
			}
			else
			{		
				printf("Enter a valid input");
			}
		}
	}while(strcmp(buf,"end")!=0);
	printf("|||||||Message Ended||||||\n");
	//		if(strcmp(buf,"bye")==0
	//			break;
	//		printf("Enter any txt to send");
	//
	//		scanf("%s",buf);
	//		printf("\n");
	//		sendto(server,buf,sizeof(buf),0,(struct sockaddr*)&clientsocket,clen);
	//	printf("Waiting for client");
	printf("Closing client\n");
	close(server);
	return 0;

}
