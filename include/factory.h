#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#define DOWN_THREAD_NUM 2
#define UP_THREAD_NUM 2
#define DOWN_TASK_NUM 1000
#define UP_TASK_NUM 300
#define MAX_CONNECT_NUM 3000
#define SOCKET_NUM 5000
#define AVG_CLIENT_NUM 30

#define MOVE(i) (i = (i+1)%UP_TASK_NUM)//任务完成的顺序不是理想的那样，这块问题太大了。

typedef struct{
    pthread_t pid;
    int fd;
    int busy_num;//正在服务的客户数量
}process_data;
typedef struct{
    int state;
    char name[30];
    int code;
    int rotate;
}client_t;

void factoryInit(process_data*,process_data*,client_t*);
void factoryStart(process_data*,process_data*);
//void factoryDistory(client_t*);
int tcpInit(int*,FILE *);
void epoll_func(int,int,int,int);
void log_port(int fd,const char *caozuo,char *name,struct sockaddr_in*clien);
void log_name(int fd,const char *caozuo,char *name);
void log_caozuo(int fd,const char *caozuo,char *neirong,char *name);
int math_task(process_data *p,int max,int);
void* down_func(void *pF);
void* upload_func(void *pF);
int tranFile(int);
#endif
