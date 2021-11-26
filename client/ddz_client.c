#include "../lib/common.h"

const char *server_ip = "127.0.0.1";
#define SERVER_PORT 6666


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
    struct requset_header *req_hdr=malloc(sizeof(struct requset_header));
    req_hdr->reqtype=LOGIN_REQ;
    struct login_req_body *login_req=malloc(sizeof(struct login_req_body));
    strcat(login_req->username,"liuhao");
    strcat(login_req->userpwd,"lh000");
    send(clientSocket,req_hdr,sizeof(struct requset_header),TCP_NODELAY);
    send(clientSocket,login_req,sizeof(struct login_req_body),TCP_NODELAY);
    sleep(1);
    close(clientSocket);
        
    return 0;
}
