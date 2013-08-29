#ifndef _DEAL_REQUEST_H
#define _DEAL_REQUEST_H
#include "mysql_connect.h"
#include <pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<ctype.h>
#include<mysql.h>
#include<stdlib.h>

typedef struct
{
	int 	id;
	char 	passwd[20];
	char 	ip[20];
	int		port;
	char 	real_ip[200];
}LOGIN_PACT;

typedef struct
{
	int 	id;
	int 	age;
	char 	name[20];
	char 	passwd[20];
	char	gender[4];
	int 	flag;
}USER_INFO;

typedef struct
{
	int 	user_id;
	int 	friend_id;
	char 	info[4096];
	time_t	chat_time;
}CHAT_PACT;


typedef struct
{
	int 		s_flag;
	int 		r_flag;
	LOGIN_PACT 	first_struct;
	USER_INFO   second_struct;
	CHAT_PACT	third_struct;
	USER_INFO 	friend_list[30];
	//FILE		record_file;
}COMBINE;

void doRequest(MYSQL *, COMBINE *);
int checkPasswd(MYSQL *, LOGIN_PACT*);
int checkRegister(MYSQL *, USER_INFO *);
int checkChatRecord(MYSQL *, CHAT_PACT *);
int checkFriendList(MYSQL *, USER_INFO *);
int checkUserInfo(MYSQL *, USER_INFO*);
int checkModifyInfo(MYSQL *, USER_INFO *);
int checkChatStart(MYSQL *, CHAT_PACT *);
int checkSaveInfo(MYSQL *, CHAT_PACT *);
int return_qq_id(MYSQL *);
void QQ_exit(MYSQL *, USER_INFO *);
int checkaddFriend(MYSQL *,CHAT_PACT *);
int lookAllUser(MYSQL *,USER_INFO *);
int addFriendValidate(MYSQL *,COMBINE *comb);
int  get_UserIp(MYSQL *,int,struct sockaddr_in*);
void getNowtime(char *);
void get_sockaddr(struct sockaddr_in *,char *);
int init_UPD_sockfd(void);
int init_TCP_sockfd(void);
int get_UDP_sockfd(void);
int get_TCP_sockfd(void);
void * listen_user(void);
void * UDP_service(MYSQL *);
#endif
