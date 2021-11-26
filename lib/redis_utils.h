#include <hiredis/hiredis.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
//command=1:set
//command=2:get
//command=3:del

static int inline redis_execute(char *key,char *value,int command_type){
    const char* login_str="auth 123456";
    //连接
    redisContext* conn = redisConnect("127.0.0.1", 6379);  
    if(conn->err)   {
        printf("[info]redis connection error:%s\n", conn->errstr);  
        return -1;
    }
    //登录
    redisReply* reply = (redisReply*)redisCommand(conn,login_str); 
    freeReplyObject(reply);

    //拼接指令
    char *command_str=malloc(128);
    memset(command_str,0,128);
    if(command_type==1){
        strcat(command_str,"set ");
        strcat(command_str,key);
        strcat(command_str," ");
        strcat(command_str,value);
    }else if(command_type==2){
        strcat(command_str,"get ");
        strcat(command_str,key);
    }else if(command_type==3){
        strcat(command_str,"del ");
        strcat(command_str,key);
    }
    //执行指令
    reply = (redisReply*)redisCommand(conn,command_str); 
    if(command_type==2 && reply->str!=NULL){
        strcpy(value,reply->str);
    }
    //释放内存
    freeReplyObject(reply);
    free(command_str);
    redisFree(conn);  
}
