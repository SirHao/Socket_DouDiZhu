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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/time.h>
/*
    int total_size = atoi(argv[1]);
    int each_size_test = atoi(argv[2]);
    int break_time = atoi(argv[3]);
*/

const char *server_ip = "127.0.0.1";
#define SERVER_PORT 6666

typedef struct test_str{
    char aa[32];
    char bb[32];
    char dd[32];
}test_str;


void do_test()
{
    int clientSocket, error, normal, ret;

    struct sockaddr_in serverAddr;

 
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);

    error = 0;
    normal = 0;

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return;
    }
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect");
        return;
    }
    test_str* cc=calloc(1,sizeof(test_str));
    strcat(cc->aa,"12345");
    strcat(cc->bb,"67890");
    strcat(cc->dd,"abcde");
    ret = send(clientSocket, cc->aa, sizeof(cc->aa), TCP_NODELAY);
    if (ret < 0)
    {
        perror("send tm");
        return;
    }else{
        printf("==========%d====%s \n",ret,cc->aa);
    }
    ret = send(clientSocket, cc->bb, sizeof(cc->bb), TCP_NODELAY);
    if (ret < 0)
    {
        perror("send tm");
        return;
    }else{
        printf("==========%d====%s \n",ret,cc->aa);
    }
    
    ret = send(clientSocket, cc->bb, sizeof(cc->bb), TCP_NODELAY);
     if (ret < 0)
    {
        perror("send tm");
        return;
    }else{
        printf("==========%d====%s \n",ret,cc->bb);
    }
    close(clientSocket);
    free(cc);
}
int main(int argc, char *argv[])
{
   
        do_test();
    
    return 0;
}
