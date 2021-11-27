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
#include <time.h>
/*
基本通信流程：
a  ->header->  b     
a  -> body ->  b  
b根据header类型判断a发送的body是什么类型（决定着recv的大小）
*/

#define LOGIN_REQ 'a' //client->server 登录
#define QUIT_REQ 'b'  //client->server 离线

#define USER_INFO_REQ 'c' //client->server 请求个人战况
#define CREATE_JOIN_ROOM_REQ 'd'   //client->server 创建/加入房间的请求
#define START_GAME_REQ 'e'  //client->server 申请发牌
#define PLAY_CARD_REQ 'f'   //client->server 出牌

