#include "handler.h"
static const char *quit_flag = "++++++";
int quit_handler(int client_fd)
{
    char sendbuf[128];
    int ret;

    struct player *ply = idm_lookup(player_map, client_fd);
    if (ply)
    {
        idm_clear(player_map, client_fd);
        printf("[info]用户%s-%d退出游戏\n",ply->name,ply->id);
        free(ply);
    }
    else
    {
        perror("[error]del null user");
    }

    memset(sendbuf, 0, sizeof(sendbuf));
    memcpy(sendbuf, quit_flag, strlen(quit_flag));
    ret = send(client_fd, sendbuf, strlen(sendbuf) + 1, TCP_NODELAY);
    printf("[debug5]发送预期%ld->实际：%d %s\n", strlen(sendbuf) + 1, ret, sendbuf);
    if (ret < 0)
    {
        perror("[info]发送退出反馈失败");
        return 0;
    }

    return 1;
}