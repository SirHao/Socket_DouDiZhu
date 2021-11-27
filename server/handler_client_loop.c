#include "handler.h"

void client_loop_handler(int client_fd){
    printf("[info] a client join fd:%d\n",client_fd);
    int ret,status=-1;
    bool quit_flag=false;
    struct requset_header*  req_header=malloc(sizeof(struct requset_header));
    
    while(1){
        ret=recv(client_fd,req_header,sizeof(struct requset_header),MSG_WAITALL);
        printf("--%d--\n",ret);
        if(ret<0 || req_header->reqtype!=LOGIN_REQ) perror("[info]recv login error:");
        else { 
            status=login_handler(client_fd);
            if(status==0) break;
            else sleep(1);
            fflush(stdout);
        }
    }
    printf("[info]start service for user\n");
    while(!quit_flag){
        int rettt=recv(client_fd,req_header,sizeof(struct requset_header),MSG_WAITALL);
        printf("=quit=%d=%d\n",rettt,req_header->reqtype);fflush(stdout);
        switch(req_header->reqtype){
            //退出
            case QUIT_REQ: 
            quit_flag=quit_handler(client_fd);
            break;
            case CREATE_ROOM_REQ: 
            case JOIN_ROOM_REQ:
                create_join_room_handler(client_fd);
            break;
            case START_GAME_REQ:
            
            break;
        }
    }
    printf("[info]用户退出游戏\n");
    free(req_header);
    

    
}
