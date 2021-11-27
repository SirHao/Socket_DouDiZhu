#include "handler.h"
static const char *win_prefix = "win:";
static const char *loss_prefix = "loss:";
int user_info_handler(int client_fd)
{
    char sendbuf[128];
    char recvbuf[128];
    char win_key[32];
    char loss_key[32];
    char win[10];
    char loss[10];
    int ret;

    memset(sendbuf, 0, sizeof(sendbuf));
    memset(recvbuf, 0, sizeof(recvbuf));
    memset(win, 0, sizeof(win));
    memset(loss, 0, sizeof(loss));
    memset(win_key, 0, sizeof(win_key));
    memset(loss_key, 0, sizeof(loss_key));

    struct player *ply = idm_lookup(player_map, client_fd);
    if (ply)
    {
        memcpy(win_key, win_prefix, strlen(win_prefix));
        memcpy(loss_key, loss_prefix, strlen(loss_prefix));
        strcat(win_key,ply->name);
        strcat(loss_key,ply->name);
        redis_execute(win_key,win,2);
        redis_execute(loss_key,loss,2);
        sprintf(sendbuf,"user:%s | win:%s | loss:%s",ply->name,win,loss);
    }
    else
    {
        sprintf(recvbuf, "...op,没查到:%d的个人信息...", client_fd);
        perror("error");
    }
    ret = send(client_fd, sendbuf, strlen(sendbuf)+1, TCP_NODELAY);
    printf("[debug8]发送预期%ld->实际：%d %s\n", strlen(sendbuf)+1,ret,sendbuf);
    if (ret < 0)
        perror("[info]发送个人信息反馈失败");

    return 0;
}