#include "handler.h"

void client_loop_handler(int client_fd){
    printf("[info] a client join fd:%d\n",client_fd);
    int ret,status=-1;
    struct requset_header*  req_header=malloc(sizeof(struct requset_header));
    
    while(1){
        ret=recv(client_fd,req_header,sizeof(struct requset_header),MSG_WAITALL);
        if(ret<0 || req_header->reqtype!=LOGIN_REQ) perror("[info]recv login error:");
        else { 
            status=login_handler(client_fd);
            if(status==0) break;
            else sleep(1);
            fflush(stdout);
        }
    }

    
}
