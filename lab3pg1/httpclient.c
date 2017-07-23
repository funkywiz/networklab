#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(void){
	struct addrinfo hints,*res;
	int sockfd;	
	char buf[2056];
	int byte_count;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	getaddrinfo("0.0.0.0","8080",&hints,&res);
	sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	printf("Connecting\n");
	connect(sockfd,res->ai_addr,res->ai_addrlen);
	printf("Connected..\n");
	char *header= "GET /new.html HTTP/1.0\r\n Host:0.0.0.0\r\n\r\n";
	send(sockfd,header,strlen(header),0);
	printf("Get data sent\n");
	printf("We are recieving data from the localhost\n");
	byte_count=recv(sockfd,buf,sizeof(buf)-1,0);	
	buf[byte_count]=0;
	printf("recv()'d %d bytes in buf-- ",byte_count);
	printf("%s",buf);
	return 0;
}
