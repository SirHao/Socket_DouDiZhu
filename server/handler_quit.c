#include "handler.h"

int quit_handler(int client_fd){
    int ret;
    struct quit_req_body*  quit_req=malloc(sizeof(struct quit_req_body));
    struct quit_rsp_body*  quit_rsp=malloc(sizeof(struct quit_rsp_body));

    ret = read(client_fd, quit_req, sizeof(struct quit_req_body));
    if (ret < 0)
        perror("[info]recv login error:");
    else{
        printf("===%d===%d\n",ret,quit_req->user_id);fflush(stdout);
    }
    struct player* ply=idm_lookup(player_map,quit_req->user_id);
    if(ply==NULL){
        perror("[quit]quit with no user");
        quit_rsp->result=-1;
    }else{
        printf("[info]user:%s-%d,quit\n",ply->name,ply->id);
        idm_clear(player_map,quit_req->user_id);
        quit_rsp->result=1;
    }
    ret=send(client_fd,quit_rsp,sizeof(struct quit_rsp_body),TCP_NODELAY);
    if(ret<0) perror("[error]send quit rsp error:");

    free(ply);
    free(quit_req);
    free(quit_rsp);
    return 0;
}