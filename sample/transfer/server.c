#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <pthread.h>
#define SERVER_PORT 6666
char recv_buf[100000];

typedef struct thread_args{
    int client;
}thread_args;

typedef struct test_str{
    char aa[32];
    char bb[32];
    char dd[32];
}test_str;

void do_recv(thread_args *ags)
{
    int client=ags->client;
    int tm,sz;
    test_str* cc=calloc(1,sizeof(test_str));
    int ret = recv(client, cc->aa, sizeof(cc->aa), MSG_WAITALL);
    if(ret<0)
        perror("ddd");
    printf("==========%d====%s \n",ret,cc->aa);
    ret = recv(client, cc->bb, sizeof(cc->aa), MSG_WAITALL);
    if(ret<0)
        perror("ddd");
    printf("==========%d====%s \n",ret,cc->bb);
    ret = recv(client, cc->bb, sizeof(cc->bb), MSG_WAITALL);
    if(ret<0)
        perror("ddd");
    printf("==========%d====%s \n",ret,cc->bb);
    
    free(cc);
    close(client);
}
int main()
{

    int serverSocket;
    struct sockaddr_in server_addr;
    struct sockaddr_in clientAddr;
    int addr_len = sizeof(clientAddr);
    int client;
    char buffer[200];
    int iDataNum;

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(serverSocket, 5) < 0)
    {
        perror("listen");
        return 1;
    }

    while (1)
    {
        int tm, sz, ret;
        client = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t *)&addr_len);
        if (client < 0)
        {
            perror("accept");
            continue;
        }
        else
        {
            thread_args *ags=malloc(sizeof(thread_args));
            ags->client=client;
            pthread_t *child = (pthread_t *)malloc(sizeof(pthread_t));
            pthread_create(child, NULL, (void *(*)(void *))do_recv, ags);
            pthread_detach(*child);
        }
    }

    close(serverSocket);

    return 0;
}
