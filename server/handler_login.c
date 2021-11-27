#include "handler.h"
static const char* key_prefix="user:";
static const char* success_flag="******";
static const char* failed_flag="xxxxxx";
int login_handler(int client_fd)
{
    char sendbuf[128];
    char recvbuf[128];
    char userkey[128];
    char key[128];
    char userpwd[128];
    char pwd[128];

    int ret, status;

    memset(recvbuf,0,sizeof(sendbuf));
    memset(userkey,0,sizeof(userkey));
    ret = recv(client_fd, recvbuf, sizeof(recvbuf),0);
    printf("[debug2]接收%d %s\n", ret,recvbuf);
    if (ret < 0)
        perror("[info]recv login error:");
    memcpy(userkey,recvbuf,sizeof(userkey));
 
    
    memset(recvbuf,0,sizeof(recvbuf));
    ret = recv(client_fd, recvbuf, sizeof(recvbuf), 0);
    printf("[debug2]接收%d %s\n", ret,recvbuf);
    if (ret < 0)
        perror("[info]recv login error:");
    memcpy(userpwd,recvbuf,sizeof(userpwd));

    memset(key,0,sizeof(key));
    memset(pwd,0,sizeof(pwd));
    memcpy(key,key_prefix,strlen(key_prefix));
    strcat(key,userkey);
    
    redis_execute(key, pwd, 2);

    memset(sendbuf,0,sizeof(sendbuf));
    if (strlen(pwd)>0 && strcmp(pwd, userpwd) == 0)
    {
        memcpy(sendbuf,success_flag,strlen(success_flag));
        status = 0;
        //printf("[info]登录成功：%s %s->%s\n", user, pwd, login_req->userpwd);
        //内存中，在全局的玩家列表创建一个玩家基本信息
        //todo：记得退出的时候销毁 free
        struct player *ply = calloc(1,sizeof(struct player));
        ply->id = client_fd;
        strcat(ply->name, userkey);
        idm_set(player_map, ply->id, ply); //存放在全局hash表player_map，索引为ply->id
        struct player *plydev = idm_lookup(player_map, ply->id);
        if (plydev)
            printf("[info]系统载入信息成功，玩家:%s-id:%d 上线\n", userkey, plydev->id);
    }
    else
    {
        memcpy(sendbuf,failed_flag,strlen(failed_flag));
        status = -1;
        printf("[info]登录失败：%s %s->%s\n", userkey, pwd, userpwd);
    }

    ret = send(client_fd, sendbuf, strlen(sendbuf)+1, TCP_NODELAY);
    printf("[debug3]发送预期%ld->实际：%d %s\n", strlen(sendbuf)+1,ret,sendbuf);
    if (ret < 0)
        perror("[info]发送登录反馈失败");
   
    return status;
}