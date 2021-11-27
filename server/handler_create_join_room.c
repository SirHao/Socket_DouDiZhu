#include "handler.h"

int create_join_room_handler(int client_fd)
{
    int ret, status;
    struct create_room_req_body *create_room_req = malloc(sizeof(struct create_room_req_body));
    struct create_room_rsp_body *create_room_rsp = malloc(sizeof(struct create_room_rsp_body));

    ret = recv(client_fd, create_room_req, sizeof(struct create_room_req_body), MSG_WAITALL);
    if (ret < 0)
        perror("[info]recv create_room error:");
    int room_num=111;
    if(create_room_req->room_number==0){
        //
    }else if(create_room_req->room_number>0){
        //
    }
    create_room_rsp->room_number=room_num;
    ret = send(client_fd, create_room_rsp, sizeof(struct create_room_rsp_body), TCP_NODELAY);
     if (ret < 0)
        perror("[info]send create_room rsp error:");
    free(create_room_req);
    free(create_room_rsp);

    
}