#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<signal.h>
#include<arpa/inet.h>
char *ROOT;
int server,client;
void startserver(char *);
void respond(int);
int main(int argc,char*argv[] )
{
	struct sockaddr_in serv;
	socklen_t addrlen=sizeof(serv);
	char c;
	char PORT[6];
	ROOT=getenv("PWD");
	strcpy(PORT,"1000");
	int slot=0;
	while((c=getopt(argc,argv,"p: r:"))!=-1){
	switch(c)
	{
		case 'r': malloc(strlen(optarg));
				strcpy(ROOT,optarg);
				break;
		case 'p': strcpy(PORT,optarg);
				break;
	}}
	printf("Server started at port no %s with ROOT dir as %s\n",PORT,ROOT);
	startserver(PORT);
	client=accept(server,(struct sockaddr*)&serv,sizeof (serv));
	if(fork()==0)
		respond();
	return 0;
}
void startserver(char *PORT){
	struct addrinfo hints,*res,*p;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;
	getaddrinfo(NULL,"5051",&hints,&res);
	for(p=res;p!=NULL;p=p->ai_next){
	server=socket(p->ai_family,p->ai_socktype,0);
	bind(server,p->ai_addr,p->ai_addrlen);
	}
	free addrinfo(res);
	listen(server,3);
}
void respond(int n)
	char mesg[1000];
	char *reqline[3],sums[5];
	int num1,num2,sum;
	recv(client,mesg,1000,0);
	printf("%s\n",mesg);
	reqline[0]=strtok(mesg,"\t");
	reqline[1]=strtok(NULL," ");
	reqline[2]=strtok(NULL," ");
	num1=atoi(reqline[0]);
	num2=atoi(reqline[2]);
	sum=num1+num2;
	itoa(sum,sums,10);
	send(client,"HTTP/1.0 200OK",17,0);
	send(client,sums,5,0);
	close(client);
	close(server);

}
	
