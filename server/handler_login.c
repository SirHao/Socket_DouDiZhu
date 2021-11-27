#include "handler.h"

int login_handler(int client_fd)
{
    int ret,status;
    struct login_req_body*  login_req=malloc(sizeof(struct login_req_body));
    struct login_rsp_body*  login_rsp=malloc(sizeof(struct login_rsp_body));
    login_rsp->result=false;
    ret = recv(client_fd, login_req, sizeof(struct login_req_body), MSG_WAITALL);
    printf("[debug2]接收%d\n",ret);
    if (ret < 0)
        perror("[info]recv login error:");
    
    char user[32] = "user:";
    char pwd[32] = {0};
    strcat(user, login_req->username);
    redis_execute(user, pwd, 2);
    if (strcmp(pwd, login_req->userpwd) == 0)
    {
        login_rsp->result=1;
        login_rsp->usr_id=client_fd;
        status=0;
        //printf("[info]登录成功：%s %s->%s\n", user, pwd, login_req->userpwd);
        //内存中，在全局的玩家列表创建一个玩家基本信息
        //todo：记得退出的时候销毁 free
        struct player * ply=malloc(sizeof(struct player));
        ply->id= client_fd;
        strcat(ply->name,login_req->username);
        idm_set(player_map,ply->id,ply);  //存放在全局hash表player_map，索引为ply->id
        struct player * plydev=idm_lookup(player_map,ply->id);
        if(plydev) printf("[info]系统载入信息成功，玩家:%s-%d 上线\n",user,plydev->id);

    }
    else
    {
        login_rsp->usr_id=-1;
        login_rsp->result=-1;
        status=-1;
        printf("[info]登录失败：%s %s->%s\n", user, pwd, login_req->userpwd);
        
    }
    ret=send(client_fd,login_rsp,sizeof(struct login_rsp_body),TCP_NODELAY);
    printf("[debug3]发送%d\n",ret);
    if(ret<0) perror("[info]发送登录反馈失败");
    free(login_req);
    free(login_rsp);
    return status;
    
}