#include "handler.h"

int start_game_handler(int ply_number, int room_no){
    if (ply_number != 2) return 0;
    
    struct dodizhu_game *game = idm_lookup(game_map, room_no);

    if ((game->cur_player_numbers) < 3)return 0;

    // 最后一个加入到房间的玩家处理游戏洗牌
    printf("[debug8]预期：第三个玩家开始洗牌\n");
    poker_shuffle_handler(room_no);
    printf("[debug10]预期：第三个玩家洗牌结束\n");
    poker_deliver_handler(room_no);
    return 1;
}