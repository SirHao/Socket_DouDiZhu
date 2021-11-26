#include "../lib/common.h"

const char *server_ip = "127.0.0.1";
#define SERVER_PORT 6666
void user_login(int clientSocket)
{
    int ret;
    struct requset_header *req_hdr = malloc(sizeof(struct requset_header));
    req_hdr->reqtype = LOGIN_REQ;
    struct login_req_body *login_req = malloc(sizeof(struct login_req_body));
    struct login_rsp_body *login_rsp = malloc(sizeof(struct login_rsp_body));
    while (1)
    {
        //TODO:改成用户输入
        strcat(login_req->username, "liuhao");
        strcat(login_req->userpwd, "lh000");

        ret = send(clientSocket, req_hdr, sizeof(struct requset_header), TCP_NODELAY);
        if (ret < 0)
            perror("[error] send1");
        else
            printf("send1");
        ret = send(clientSocket, login_req, sizeof(struct login_req_body), TCP_NODELAY);
        if (ret < 0)
            perror("[error] send2");
        else
            printf("send2");
        fflush(stdout);
        ret=recv(clientSocket,login_rsp,sizeof(struct login_rsp_body),0);
        if (ret < 0)
            perror("[error] recv");
        else if (login_rsp->result == 1)
        {
            printf("登录成功\n");
            break;
        }
        else
        {
            printf("登录失败\n");
        }
    }
    free(login_req);
    free(login_rsp);
    free(req_hdr);
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

    while(1){
        int command=0;
        printf("input your choice:(1:get person info),(2:create a room)\n");
        printf("                  (3:join a room    ),(4:quit         )\n");
        scanf("%d",&command);
    }

    close(clientSocket);

    return 0;
}
