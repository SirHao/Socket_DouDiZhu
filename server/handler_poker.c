#include "handler.h"


/*
 *  Utils
 */
char orders[15] = {'3', '4', '5', '6', '7', 
                        '8', '9', 'T', 'J', 'Q', 
                        'K', 'A', '2', 'X', 'Y'};

int poker_bigger(char a, char b){
    int ia = 0, ib = 0;
    for (int i = 0; i < 15; i++){
        if (orders[i] == a) ia = i;
        if (orders[i] == b) ib = i;
    }
    return ia > ib;
}

void order_pokers(char pokers[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 1; j < n - i; j++){
            if (poker_bigger(pokers[j - 1], pokers[j])){
                char tmp = pokers[j];
                pokers[j] = pokers[j - 1];
                pokers[j - 1] = tmp;
            }
        }
    }
}
/*
 *  end Utils
 */




int poker_shuffle_handler(int room_no){
    char pokers[54] = {
        'A', 'A', 'A', 'A',
        '2', '2', '2', '2',
        '3', '3', '3', '3',
        '4', '4', '4', '4',
        '5', '5', '5', '5',
        '6', '6', '6', '6',
        '7', '7', '7', '7',
        '8', '8', '8', '8',
        '9', '9', '9', '9',
        'T', 'T', 'T', 'T',
        'J', 'J', 'J', 'J',
        'Q', 'Q', 'Q', 'Q',
        'K', 'K', 'K', 'K',
        'X', 'Y'
    };
    // 随机洗牌
    srand(time(0));
    for (int i = 0; i < 54; i++){
        int ri = rand() % 54;
        char tmp = pokers[i];
        pokers[i] = pokers[ri]; 
        pokers[ri] = tmp;
    }
    printf("[debug9]Info：第三个玩家洗牌中\n");
    
    // 发牌
    struct dodizhu_game *game = idm_lookup(game_map, room_no);
    if (game != NULL){
        for (int i = 0; i < 54; i++){
            game->pokers[i / 18][i % 18] = pokers[i];
        }
    }

    // 排序
    order_pokers(game->pokers[0], 18);
    order_pokers(game->pokers[1], 18);
    order_pokers(game->pokers[2], 18);
}

int poker_deliver_handler(int room_no){
    int ret;
    char sendbuf[18];
    struct dodizhu_game *game = idm_lookup(game_map, room_no);

    if (game != NULL){
        for (int i = 0; i < 3; i++){
            int client_fd = game->players[i];
            
            memcpy(sendbuf, game->pokers[i], sizeof(sendbuf));
            ret = send(client_fd, sendbuf, strlen(sendbuf), 0);
            printf("[debug13]预期18 - 发送%d  pokers(%s)\n", ret, sendbuf);
            if (ret < 0)
                perror("[info]server send pokers_body error:");
        }
    }

}