#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
/*
基本通信流程：
a  ->header->  b     
a  -> body ->  b  
b根据header类型判断a发送的body是什么类型（决定着recv的大小）
*/
enum REQ_TYPE
{
    LOGIN_REQ, //client->server 登录
    QUIT_REQ,  //client->server 离线

    CREATE_ROOM_REQ, //client->server 创建房间请求
    JOIN_ROOM_REQ,   //client->server 加入房间的请求
    START_GAME_REQ,  //client->server 申请发牌
    PLAY_CARD_REQ,   //client->server 出牌

} req_type;

enum RSP_TYPE
{
    LOGIN_RSP, //server->client LOGIN_REQ：   登录，返回个人数据；or 登录失败
    QUIT_RSP,  //server->client 响应QUIT_REQ：清理数据随后断开连接

    CREATE_ROOM_RSP, //server->client 响应CREATE_ROOM_REQ：创建房间的
    JOIN_ROOM_RSP,   //server->client 响应JOIN_ROOM_REQ：  加入房间的人数
    START_GAME_RSP,  //server->client 响应START_GAME_REQ： 发牌
    PLAY_CARD_RSP,   //server->client 响应PLAY_CARD_REQ：出牌结果（验证是否成功），成功后会调用Updata_game_msg主动推送
    UPDATE_GAME_MSG  //【最重要】server->client 主动推送，更行当前战况（谁是地主，该谁出牌，自己的牌，谁赢了）

} rsp_type;
/*
 * header
 */
struct requset_header
{
    enum REQ_TYPE reqtype;
};

struct response_header
{
    enum RSP_TYPE rsptype;
};

/*
 * bodys
 */
struct login_req_body
{
    char username[32];
    char userpwd[32];
};

struct login_rsp_body
{
    int usr_id;
    int result;
};

struct quit_req_body
{
    int user_id;
};

struct quit_rsp_body
{
    int result;
};

struct create_room_req_body
{
    int room_number;
};

struct create_room_rsp_body
{
    int room_number;
};

struct join_room_req_body
{
};

struct join_room_rsp_body
{
};

struct start_game_req_body
{
};

struct start_game_rsp_body
{
};

struct play_card_req_body
{
};

struct play_card_rsp_body
{
};
