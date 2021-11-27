1.redis环境配置
redis数据库安装: 
> sudo apt-get install redis-server redis-tools

检查是否安装成功：
> ps -aux|grep redis
配置
> vim /etc/redis/redis.conf #修改:supervised no->supervised systemd, requirepass foobared-> requirepass 123456
> systemctl restart redis

验证：redis-cli进入交互界面
    > auth 123456 #登录
    > set user:liuhao lh000
    > set user:hanjianyu hjy000
    > set user:mengxuanqi mxq000
    > set user:herenyuan hry000

    > set win:liuhao 1
    > set win:hanjianyu 9
    > set win:mengxuanqi 8
    > set win:herenyuan 7

    > set loss:liuhao 7
    > set loss:hanjianyu 2
    > set loss:mengxuanqi 1
    > set loss:herenyuan 10


    > get user:liuhao #返回b

2. c语言使用redis
> git clone git@github.com:redis/hiredis.git
> cd hiredis
> make
> make install
> cp libhiredis.so /usr/lib
> cp libhiredis.so /usr/lib32
> /sbin/ldconfig

然后sample/redis_test的redis_client：
> make && ./redis_client

