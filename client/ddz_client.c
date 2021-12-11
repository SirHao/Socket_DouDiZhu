#include "../lib/common.h"

const char *server_ip = "127.0.0.1";
#define SERVER_PORT 6666

int user_quit(int clientSocket)
{
    int ret;
    char sendbuf[128];
    char recvbuf[128];

    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(sendbuf));

    sendbuf[0] = 'b';
    ret = send(clientSocket, (char *)sendbuf, strlen(sendbuf), 0);
    printf("[debug4]发送%d\n", ret);
    if (ret < 0)
        perror("[info]send login error:");

    memset(recvbuf, 0, sizeof(recvbuf));
    ret = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
    printf("[debug5]接收%d %s\n", ret, recvbuf);
    fflush(stdout);
    if (ret < 0)
        perror("[error] recv");
    else if (strcmp("++++++", recvbuf) == 0)
    {
        printf("退出成功\n");
        fflush(stdout);
        return 1;
    }
    else
    {
        printf("退出失败\n");
        return 0;
    }
}
void user_login(int clientSocket)
{
    static const char *success_flag = "******";
    int ret;
    char sendbuf[128];
    char recvbuf[128];
    while (1)
    {
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));

        sendbuf[0] = 'a';
        ret = send(clientSocket, (char *)sendbuf, strlen(sendbuf), 0);
        printf("[debug1]发送%d\n", ret);
        if (ret < 0)
            perror("[info]send login error:");

        memset(sendbuf, 0, sizeof(sendbuf));
        printf("user name:");
        scanf("%s", sendbuf);
        ret = send(clientSocket, sendbuf, strlen(sendbuf), 0);
        printf("[debug2]发送%d\n", ret);
        if (ret < 0)
            perror("[error] send2");

        memset(sendbuf, 0, sizeof(sendbuf));
        printf("pwd:");
        scanf("%s", sendbuf);
        ret = send(clientSocket, sendbuf, strlen(sendbuf), 0);
        printf("[debug2]发送%d\n", ret);
        if (ret < 0)
            perror("[error] send2");

        memset(recvbuf, 0, sizeof(recvbuf));
        ret = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
        printf("[debug3]接收%d %s\n", ret, recvbuf);
        fflush(stdout);
        if (ret < 0)
            perror("[error] recv");
        else if (strcmp("******", recvbuf) == 0)
        {
            printf("登录成功\n");
            fflush(stdout);
            break;
        }
        else
        {
            printf("登录失败\n");
        }
    }
}
void user_create_join_room(int clientSocket)
{

    char sendbuf[128];
    char recvbuf[128];
    int ret;

    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));

    sendbuf[0] = 'd';
    ret = send(clientSocket, (char *)sendbuf, strlen(sendbuf), 0);
    printf("[debug4]发送%d\n", ret);
    if (ret < 0)
        perror("[info]send login error:");

    memset(sendbuf, 0, sizeof(sendbuf));
    printf("input room number, '0' means create a room > ");
    scanf("%s", sendbuf);
    ret = send(clientSocket, sendbuf, strlen(sendbuf), 0);
    printf("[debug6]发送%d\n", ret);
    if (ret < 0)
        perror("[error] send2");

    memset(recvbuf, 0, sizeof(recvbuf));
    ret = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
    printf("[debug7]接收%d %s\n", ret, recvbuf);
    fflush(stdout);
    if (ret < 0)
        perror("[error] recv");
    else
    {
        printf("[info]您的房间号为：%s\n", recvbuf);
    }
}

void user_info(int clientSocket)
{
    int ret;
    char sendbuf[128];
    char recvbuf[128];

    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));

    sendbuf[0] = 'c';
    ret = send(clientSocket, (char *)sendbuf, strlen(sendbuf), 0);
    printf("[debug4]发送%d\n", ret);
    if (ret < 0)
        perror("[info]send login error:");

   
    ret = recv(clientSocket, (char *)recvbuf, sizeof(recvbuf), 0);
    printf("[debug8]接收%d\n", ret);
    if (ret < 0)
        perror("[info]send login error:");
    else{
        printf("=========个人积分==========\n");
        printf("%s\n",recvbuf);
        printf("=========-------==========\n");

    }
}

void user_wait_pokers(int clientSocket){
    char recvbuf[18];
    int ret;

    memset(recvbuf, 0, sizeof(recvbuf));
    ret = recv(clientSocket, recvbuf, sizeof(recvbuf), 0);
    printf("[debug16]接收%d (%s)\n", ret, recvbuf);
    fflush(stdout);
    if (ret < 0){
        perror("[info]receive pokers error:");
    }else{
        printf("[info]Recv Pokers: (%s)\n", recvbuf);
        printf("[info]Your Pokers:\n");
        for (int i = 0; i < 18; i++){
            if (recvbuf[i] == 'T')
                printf("10 ");
            else
                printf("%c ", recvbuf[i]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int clientSocket, error, normal, ret;
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[error] socket create: ");
        return -1;
    }
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("[error] connect server: ");
        return -1;
    }
    user_login(clientSocket);
    int quit_flag = -1;
    while (1)
    {
        int command = 0;
        printf("input your choice:(1:get person info),(2:create/join a room),(3:quit)\n");
        scanf("%d", &command);
        if (command == 1)
        {
            user_info(clientSocket);
        }
        else if (command == 2)
        {
            user_create_join_room(clientSocket);
            // 等待客户端发牌
            user_wait_pokers(clientSocket);
        }
        else if (command = 3)
        {
            quit_flag = user_quit(clientSocket);
            if (quit_flag == 1)
                break;
            else
                continue;
        }
        else
        {
            printf("[info]请提供正确的指令\n");
        }
    }

    close(clientSocket);

    return 0;
}
