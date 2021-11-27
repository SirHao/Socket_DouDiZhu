#include "../lib/common.h"

const char *server_ip = "127.0.0.1";
#define SERVER_PORT 6666

int global_user_id = 0;
int user_quit(int clientSocket)
{
    int ret;
    struct requset_header *req_hdr = malloc(sizeof(struct requset_header));
    req_hdr->reqtype = QUIT_REQ;
    struct quit_req_body *quit_req = malloc(sizeof(struct quit_req_body));
    struct quit_rsp_body *quit_rsp = malloc(sizeof(struct quit_rsp_body));
    ret = send(clientSocket, req_hdr, sizeof(struct requset_header), TCP_NODELAY);
    if (ret < 0)
        perror("[error] send1");
    else
    {
        printf("--send quit1:%d--\n", ret);
    }

    quit_req->user_id = 0;
    printf("[info]===%d===%d\n", ret, quit_req->user_id);
    ret = send(clientSocket, quit_req, sizeof(struct quit_req_body), TCP_NODELAY);
    if (ret < 0)
        perror("[error] send2");
    else
    {
        printf("--send quit2:%d--\n", ret);
    }
    fflush(stdout);
    ret = recv(clientSocket, quit_rsp, sizeof(struct quit_rsp_body), 0);
    if (ret < 0)
    {
        perror("[error] recv");
        ret = -1;
    }
    else
    {
        if (quit_rsp->result == 1)
        {
            printf("[info]退出成功，服务端已清理数据\n");
            ret = 1;
        }
        else
        {
            printf("[info]退出失败\n");
            ret = -1;
        }
    }
    free(quit_req);
    free(quit_rsp);
    free(req_hdr);
    return ret;
}
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
        ret = send(clientSocket, login_req, sizeof(struct login_req_body), TCP_NODELAY);
        if (ret < 0)
            perror("[error] send2");
        fflush(stdout);
        ret = recv(clientSocket, login_rsp, sizeof(struct login_rsp_body), 0);
        if (ret < 0)
            perror("[error] recv");
        else if (login_rsp->result == 1)
        {
            global_user_id = login_rsp->usr_id;
            printf("登录成功,用户id为%d\n", global_user_id);
            fflush(stdout);
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
void user_create_join_room(int clientSocket, int room_number)
{
    int ret;
    struct requset_header *req_hdr = malloc(sizeof(struct requset_header));
    struct create_room_req_body *create_room_req = malloc(sizeof(struct create_room_req_body));
    struct create_room_rsp_body *create_room_rsp = malloc(sizeof(struct create_room_rsp_body));

    req_hdr->reqtype = CREATE_ROOM_REQ;
    ret = send(clientSocket, req_hdr, sizeof(struct requset_header), TCP_NODELAY);
    create_room_req->room_number = room_number;
    ret = send(clientSocket, create_room_req, sizeof(struct create_room_req_body), TCP_NODELAY);
    if (ret < 0)
        perror("[error] send2");
    ret = recv(clientSocket, create_room_rsp, sizeof(struct create_room_rsp_body), MSG_WAITALL);
    if (ret < 0)
        perror("[error] recv create room");
    printf("[info]成功加入/创建房间:%d\n",create_room_rsp->room_number);
    free(create_room_req);
    free(create_room_rsp);
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
    int quit_flag = -1;
    while (1)
    {
        int command = 0;
        printf("input your choice:(1:get person info),(2:create a room)\n");
        printf("                  (3:join a room    ),(4:quit         )\n");
        scanf("%d", &command);
        if (command == 1)
        {
        }
        else if (command == 2)
        {
            user_create_join_room(clientSocket,0);
        }
        else if (command == 3)
        {
        }
        else if (command = 4)
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
