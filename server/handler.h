#include "../lib/common.h"
#include "../lib/redis_utils.h"
#include "index_map.h"


struct player {
    int id;
    char name[32];
    void* ddz;
};

struct dodizhu_game{
    int room_number;
    int cur_player_numbers;
    int players[3];   //都是id
    char pokers[3][18];
};


struct index_map *player_map;
struct index_map *game_map;


void client_loop_handler(int client_fd);
int login_handler(int client_fd);
int quit_handler(int client_fd);
int create_join_room_handler(int client_fd);
int user_info_handler(int client_fd);

int poker_shuffle_handler(int room_no);
int poker_deliver_handler(int room_no);