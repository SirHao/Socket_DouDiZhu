#include "handler.h"
static const char *room_number_error = "<your room number error>";
static const char *room_no_space = "<your room is full>";
int create_join_room_handler(int client_fd)
{
    char sendbuf[128];
    char recvbuf[128];
    struct dodizhu_game *game;
    struct player *ply;
    int room_no, ret, join_result = 3;

    ply = idm_lookup(player_map, client_fd);
    if (!ply)
    {
        perror("[error] cannot find player when join room");
        goto create_join_room_end;
    }

    memset(recvbuf, 0, sizeof(recvbuf));
    memset(sendbuf, 0, sizeof(sendbuf));
    ret = recv(client_fd, recvbuf, sizeof(recvbuf), 0);
    printf("[debug6]接收%d %s\n", ret, recvbuf);
    if (ret < 0)
        perror("[info]recv join/create error:");

    // body = 0，创建房间的请求
    if (strcmp("0", recvbuf) == 0)
    {
        srand((unsigned)time(NULL));
        while (1)
        {
            // 随机摇房间号
            room_no = rand() % 1023 + 1;
            // 查找房间号是否摇重了，重了就利用while重新摇
            game = idm_lookup(game_map, room_no);
            if (!game)
            {
                game = calloc(1, sizeof(struct dodizhu_game));
                game->room_number = room_no;
                idm_set(game_map, room_no, game);
                ply->ddz = (void *)game;
                game->cur_player_numbers = 1;
                game->players[0] = client_fd;
                printf("[info]user:%s create room:%d\n", ply->name, game->room_number);
                join_result = 1;
                break;
            }
        }
    }
    // body != 0，加入房间的请求
    else
    {
        room_no = atoi(recvbuf);
        if (room_no > 0)
        {
            game = idm_lookup(game_map, room_no);
            if (game != NULL)
            {
                if ((game->cur_player_numbers) < 3)
                {
                    game->players[game->cur_player_numbers] = client_fd;
                    game->cur_player_numbers++;
                    join_result = 2;
                }
                else
                    join_result = 3;
            }
        }
        else
        {
            join_result = 4;
            goto create_join_room_end;
        }
        printf("[info]user:%d join room:%s\n", client_fd, recvbuf);
    }

create_join_room_end:

    memset(sendbuf, 0, sizeof(sendbuf));
    // 1: 创建房间成功
    if (join_result == 1)
    {
        sprintf(sendbuf, "@create: %d @", room_no);
    }
    // 2: 加入房间成功
    else if (join_result == 2)
    {
        sprintf(sendbuf, "@join: %d @", room_no);
    }
    // 3: 要加入的房间已经满3个人
    else if (join_result == 3)
    {
        memcpy(sendbuf, room_no_space, strlen(room_no_space));
    }
    // 4: 房间号为负，命令不合法
    else
    {
        memcpy(sendbuf, room_number_error, strlen(room_number_error));
    }
    ret = send(client_fd, sendbuf, strlen(sendbuf) + 1, 0);
    printf("[debug7]发送预期%ld->实际：%d %s\n", strlen(sendbuf) + 1, ret, sendbuf);
    if (ret < 0)
        perror("[info]发送登录反馈失败");

    if (join_result == 2){
        // 最后一个加入到房间的玩家处理游戏洗牌
        if ((game->cur_player_numbers) == 3){
            printf("[debug8]预期：第三个玩家开始洗牌\n");
            poker_shuffle_handler(room_no);
            printf("[debug10]预期：第三个玩家洗牌结束\n");
            poker_deliver_handler(room_no);
        }
    }
    return 0;
}