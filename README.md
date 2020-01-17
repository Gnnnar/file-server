# file-server
User management and file transfer
这是一个文件管理服务器的项目，在功能上模仿百度网盘的基础功能。分为四个部分
第一：用户管理
    表：name salt niptxt token
    用sha-512算法对用户的密码加密在网络中传输，用token值对断开重连的用户进行认证
第二：虚拟目录设计
    表：code procode belongID filename filetype filesize md5sum
    服务器将所有用户的文件放在一个文件夹下，通过数据库虚拟目录的设计，实现用户仅可以查看到自己的文件并执行相应的操作
第三：协议设计
    struct tran_t
    {
        int len;
        int ctl_code;
        char buf[10240]
    };
    服务器与客户端用这个结构体通信，客户端EPOLL监控标准输入和服务器SOCKETFD，对标准输入进行字符串解析后执行相应的操作，
    对服务器数据进行拆包后根据相应的ctl_code执行对应得操作
    struct client
    {
        int state；
        int code;
        int rota;
        char name[30]
     }
     服务器对每一条accept后的链接视为一个用户，维护上面的结构体的信息，并进行EPOLL监控读事件。对读到的事件拆包后，根据ctl_code执行相应的操作
第四：上传和下载的实现
    客户端与服务器的主线程用于各种命令的通信，上传和下载这种耗时的操作都交给子线程去做，我在两边都采用的管道进行主线程和子线程的通信
    服务器把上传线程和下载线程分开了
    最后实现了一下多点下载。
问题：
    1：最严重的问题--服务器拒绝式攻击，都用的阻塞性编程。问题太大
    2：当时EPOLL事件判断用的==，而不是& 所以在同时监控读写事件时出现BUG
    3：轮盘超时用的方法太low，效率不高
