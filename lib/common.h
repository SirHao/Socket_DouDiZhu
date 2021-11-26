#include<stdio.h>
/*
基本通信流程：
a  ->header->  b     
a  -> body ->  b  
b根据header类型判断a发送的body是什么类型（决定着recv的大小）
*/
typedef enum REQ_TYPE {
    LOGIN_REQ;       //client->server 登录
    QUIT_REQ;        //client->server 离线

    CREATE_ROOM_REQ; //client->server 创建房间请求
    JOIN_ROOM_REQ;   //client->server 加入房间的请求
    START_GAME_REQ;  //client->server 申请发牌
    PLAY_CARD_REQ;   //client->server 出牌
    QUIT_REQ;        //client->server 离线

}REQ_TYPE;

typedef enum RSP_TYPE {
    LOGIN_RSP;         //server->client LOGIN_REQ：   登录，返回个人数据；or 登录失败
    QUIT_RSP;          //server->client 响应QUIT_REQ：清理数据随后断开连接

    CREATE_ROOM_RSP;   //server->client 响应CREATE_ROOM_REQ：创建房间的
    JOIN_ROOM_RSP;     //server->client 响应JOIN_ROOM_REQ：  加入房间的人数
    START_GAME_RSP;    //server->client 响应START_GAME_REQ： 发牌
    PLAY_CARD_RSP;     //server->client 响应PLAY_CARD_REQ：出牌结果（验证是否成功），成功后会调用Updata_game_msg主动推送
    UPDATE_GAME_MSG;   //【最重要】server->client 主动推送，更行当前战况（谁是地主，该谁出牌，自己的牌，谁赢了）
    
}RSP_TYPE;
/*
 * header
 */
struct typedef requset_header{
    REQ_TYPE type;
}requset_header;

struct typedef response_header{
    RSQ_TYPE type;
}response_header;

/*
 * bodys
 */
struct  typedef login_req_body{

}login_req_body;

struct  typedef login_rsp_body{

}login_rsp_body;

struct  typedef quit_req_body{

}quit_req_body;

struct  typedef quit_rsp_body{

}quit_rsp_body;

struct  typedef create_room_req_body{

}create_room_req_body;

struct  typedef create_room_rsp_body{

}create_room_rsp_body;

struct  typedef join_room_req_body{

}join_room_req_body;

struct  typedef join_room_rsp_body{

}join_room_rsp_body;

struct  typedef start_game_req_body{

}start_game_req_body;

struct  typedef start_game_rsp_body{

}start_game_rsp_body;

struct  typedef play_card_req_body{

}play_card_req_body;

struct  typedef play_card_rsp_body{

}play_card_rsp_body;


