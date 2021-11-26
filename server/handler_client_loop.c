#include "handler.h"

void client_loop_handler(int client_fd){
    printf("[info] a client join fd:%d\n",client_fd);
    int ret,status=-1;
    struct requset_header*  req_header=malloc(sizeof(struct requset_header));
    struct login_req_body*  login_req=malloc(sizeof(struct login_req_body));
    while(status==-1){
        ret=recv(client_fd,req_header,sizeof(struct requset_header),MSG_WAITALL);
        if(ret<0 || req_header->reqtype!=LOGIN_REQ) perror("[info]recv login error:");
        else {
            ret=recv(client_fd,login_req,sizeof(struct login_req_body),MSG_WAITALL);
            if(ret<0) perror("[info]recv login error:");
            sleep(1);
            char user[32]="user:";
            char pwd[32]={0};
            strcat(user,login_req->username);
            redis_execute(user,pwd,2);
            if(strcmp(pwd,login_req->userpwd)==0) {
                status=0;
                printf("[info]登录成功：%s %s->%s\n",user,pwd,login_req->userpwd);
            }else{
                printf("[info]登录失败：%s %s->%s\n",user,pwd,login_req->userpwd);
            }
            fflush(stdout);
            
        }
    }

    free(login_req);
}
