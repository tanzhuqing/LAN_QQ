#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "qq_ui.h"

#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#define IDRECORD 200
int 	 sockfd;
int 	 current_user_id;
int      select_user_id;
struct 	 sockaddr_in my_addr;
char 	 youSay[4096];
socklen_t socket_len;

typedef struct
{
	int 	id;
	char 	passwd[20];
	char 	ip[20];
	int     port;
	char	real_ip[200];
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
	time_t 	chat_time;
}CHAT_PACT;

typedef struct
{
	int 		s_flag;
	int 		r_flag;
	LOGIN_PACT 	first_struct;
	USER_INFO   second_struct;
	CHAT_PACT	third_struct;
	USER_INFO   friend_list[30];
}COMBINE;

struct 
{
	int id;
	HWND hwnd;
	char heSay[10000];

}id_win_chat[20];


void 	connect_server(void);
void 	setSockfd(int);

int 	getSockfd(void);
void * 	waitCombine(void *);
void * 	pthreadInitFriendlist(void *);
void *  newWindow(void *);

int 	classifyReceive(COMBINE);
int 	checkPasswd(char *, char *);
int 	checkRegister(char *, char *, char *, char *, char *);
void 	sendChatText(int ,int , char *);
//int sendChatText(int ,int , char *, time_t);



void	setCurrentUserID(int);
int		getCurrentUserID(void);

void 	setSelectUserID(int);
int 	getSelectUserID(void);

void 	saveIDWin(int , HWND);
void 	deleteIDWin(int);
HWND 	getWinbyID(int);
int		getIDbyWin(HWND);
int 	getIndexbyID(int);
int 	getIndexbyWin(HWND);

/*	use for testing	*/
void 	justTest();
void 	printHwnd(HWND);

void  get_info(int friend_id,unsigned char buff[]);
 void  save_info(COMBINE tags);
													
