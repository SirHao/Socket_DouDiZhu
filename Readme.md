# Socket DouDiZhu
**基于socket通信的client/server架构斗地主**[2021秋季高级计算机网络小组项目]
> 小组成员:mengxuanqi liuhao hanjianyu herenyuan
+ license: MIT 2.0

项目结构：
redis存放用户密码，胜负次数
```
lib        
|-common.h  //通信的消息格式,提供给server client作为通信规范
|-redis.h   //redis执行命令的内联函数，提供给server读写数据库
docs
|-redis.md  //redis安装过程
sample
|-redis    //redis使用示例
client     //斗地主客户端
server     //斗地主服务端
|-ddz_server.c //主函数，每一个用户建立连接后，交给交给handler_client_loop处理
|-handler_client_loop.c //处理单个用户的逻辑主函数，接下来的细节动作交给handlerxx处理
|-handler_login.c       //处理用户登录的逻辑
```

## 环境搭建
1. 根据docs/redis搭建
2. 在server下运行服务端
```
make
./ddz_s

```  
3. 在client下运行客户端
```
make
./ddz_c

```  