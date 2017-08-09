#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(void)
{
        int s,s2,t,len,cp;
        struct sockaddr_in local,rem;
        char str[100];
        s=socket(AF_INET,SOCK_STREAM,0);
        if(s==-1)
        {
                perror("socket");
                exit(1);
        }
        bzero((char *)&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(5559);
        local.sin_addr.s_addr=inet_addr("127.0.0.1");
        if(bind(s,(struct sockaddr *)&local,sizeof(local))==-1)
        {
                perror("bind");
                exit(1);
        }
        if(listen(s,5)==-1)
        {
                perror("listen");
                exit(1);
        }
	while(1)
        {
                int done,n;
                t=sizeof(rem);
                s2=accept(s,(struct sockaddr *)&rem,&t);
                if(s2==-1)
                {
                        perror("accept");
                        exit(1);
                }
		printf("connected \n");
                if((cp=fork())<0)
                {
                        perror("fork error");
                }
                else if(cp==0)
                {
                        close(s);
                        done=0;
                        do
                        {
                                n=recv(s2,str,sizeof(str),0);
                                printf("Message from a client..%s \n",str);
                                if(n<=0)
                                {
                                        if(n<0)
                                                perror("recv");
                                        done=1;
                                }
                                if(!done)
				printf("\n");
				printf("Enter any msg");
				scanf("%s",str);
                                if(send(s2,str,n,0)<0)
                                {
                                        perror("send");
                                        done=1;
                                }
                        }while(!done);
                        exit(0);
                }
                close(s2);
        }
        return 0;
}
