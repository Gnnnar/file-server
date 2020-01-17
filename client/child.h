#ifndef __CHILD_H__
#define __CHILD_H__
#include "head.h"
#include "cfactory.h"
#define DOWN_PATH "./Cdisk/"

extern struct sockaddr_in ser;
extern Zhuce login_msg;
extern char path[];

typedef struct{
    pthread_t pid;
    int fd;
    int busy_num;
}process_data;

typedef struct{
    int number;
    int state;
    int start;
    int end;
}Section;

typedef struct{
    Section sec[SECTION_NUM];
    int sfd[SPOT_NUM];
    int ffd;
    int tfd;
    char *p;
    MQ_buf mq;
//    char *tp;
}Package;

typedef struct{
    int start;
    int end;
    int number;
    char md5sum[50];
}BBQ;

void *normal_func(void*);
void *vip_func(void*);


#endif
