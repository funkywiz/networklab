#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	FILE *fp;
	struct sockaddr_in server,client;
	int s,n;
	char b1[100],b2[100],a[100];
	s=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_port=3000;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	bind(s,(struct sockaddr *)&server,sizeof(server));
	n=sizeof(client);
	while(1)
	{
		recvfrom(s,b1,sizeof b1, 0,(struct sockaddr *)&client,&n);
		sendto(s,"Bind Successful",sizeof("Bind Successful"),0,(struct sockaddr *)&client,n);
		sendto(s,"Searching in local DNS",sizeof("Searching in local DNS"),0,(struct sockaddr *)&client,n);
		strcpy(b2,"");
		fp=fopen("/etc/hosts","r");
		while(!feof(fp))
		{
			fscanf(fp,"%s",a);
			if(strcmp(a,b1)==0)
			{
				fscanf(fp,"%s",b2);
				break;
			}
		}
		if(strcmp(b2,"")==0)
		{
			strcpy(b2,"Not found...");	   
		}
		fclose(fp);
		sendto(s,b2,sizeof b2,0,(struct sockaddr *)&client,n);
		if(strcmp(b2,"Not found...")==0)
		{
			sendto(s,"Searching in TLD",sizeof("Searching in TLD"),0,(struct sockaddr *)&client,n);
			strcpy(b2,"");
			fp=fopen("tld.txt","r");
			while(!feof(fp))
			{
				fscanf(fp,"%s",a);
				if(strcmp(a,b1)==0)
				{
					fscanf(fp,"%s",b2);
					break;
				}
			}
			if(strcmp(b2,"")==0)
			{
				strcpy(b2,"Not found...");
			}
			fclose(fp);
			sendto(s,b2,sizeof b2,0,(struct sockaddr *)&client,n);
			if(strcmp(b2,"Not found...")==0)
			{
				sendto(s,"Searching in AUTHORITATIVE",sizeof("Searching in AUTHORITATIVE"),0,(struct sockaddr *)&client,n);
				strcpy(b2,"");
				fp=fopen("auth.txt","r");
				while(!feof(fp))
				{
					fscanf(fp,"%s",a);
					if(strcmp(a,b1)==0)
					{
						fscanf(fp,"%s",b2);
						break;
					}
				}
				if(strcmp(b2,"")==0)
				{
					strcpy(b2,"Not found...");
				}
				fclose(fp);
				sendto(s,b2,sizeof b2,0,(struct sockaddr *)&client,n);
				sendto(s,"bye",sizeof ("bye"),0,(struct sockaddr *)&client,n);
			}
			else
				sendto(s,"bye",sizeof ("bye"),0,(struct sockaddr *)&client,n);


		}
		else
			sendto(s,"bye",sizeof ("bye"),0,(struct sockaddr *)&client,n);


	}
	return 0;
}
