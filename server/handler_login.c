#include "handler.h"

int login_handler(int client_fd)
{
    int ret,status;
    struct login_req_body*  login_req=malloc(sizeof(struct login_req_body));
    struct login_rsp_body*  login_rsp=malloc(sizeof(struct login_rsp_body));
    login_rsp->result=false;
    ret = recv(client_fd, login_req, sizeof(struct login_req_body), MSG_WAITALL);
    if (ret < 0)
        perror("[info]recv login error:");
    char user[32] = "user:";
    char pwd[32] = {0};
    strcat(user, login_req->username);
    redis_execute(user, pwd, 2);
    if (strcmp(pwd, login_req->userpwd) == 0)
    {
        login_rsp->result=true;
        status=0;
        printf("[info]登录成功：%s %s->%s\n", user, pwd, login_req->userpwd);
    }
    else
    {
        login_rsp->result=false;
        status=-1;
        printf("[info]登录失败：%s %s->%s\n", user, pwd, login_req->userpwd);
        
    }
    ret=send(client_fd,login_rsp,sizeof(struct login_rsp_body),TCP_NODELAY);
    if(ret<0) perror("[info]发送登录反馈失败");
    free(login_req);
    free(login_rsp);
    return status;
    
}