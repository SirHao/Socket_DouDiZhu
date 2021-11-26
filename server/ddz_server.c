#include "handler.h"
#define SERVER_PORT 6666

typedef struct thread_args{
    int client;
}thread_args;

void client_handler(thread_args *ags)
{
    int client=ags->client;

    client_loop_handler(client);

    free(ags);
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
    }else{
        printf("[info]init success,start listen for client\n");
        fflush(stdout);
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
            pthread_t *child = (pthread_t *)malloc(sizeof(pthread_t));
            ags->client=client;
            pthread_create(child, NULL, (void *(*)(void *))client_handler, ags);
            pthread_detach(*child);
        }
    }

    close(serverSocket);

    return 0;
}
