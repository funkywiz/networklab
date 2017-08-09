#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 5054
int main()
{
        int slen,clen,rc;
        int server,client;
        struct sockaddr_in serversocket,clientsocket;
        char buf[1024];
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
        while(1){
                recvfrom(server,buf,sizeof(buf),0,(struct sockaddr*)&clientsocket,&clen);
                if(strcmp(buf,"bye")==0)
                        break;
		execl(buf,buf,0);
        }
        close(server);
        return 0;

}

