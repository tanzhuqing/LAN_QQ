#include "client.h"

//int sockfd;
//struct 	 sockaddr_in my_addr;
//socklen_t socket_len;

void connect_server(void)
{	
	socket_len=sizeof(struct sockaddr);
	setSockfd(socket(AF_INET,SOCK_DGRAM,0));
	my_addr.sin_family		= AF_INET;

	//liadingshi's computer
	my_addr.sin_addr.s_addr = inet_addr("192.168.1.253");
	my_addr.sin_port		= htons(4443);

}

void setSockfd(int _sockfd)
{
	sockfd=_sockfd;
}

int getSockfd(void)
{
	return sockfd;
}


int classifyReceive(COMBINE comb)
{
		if(recvfrom(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr,&socket_len)<0)	
	{	
		perror("receive error\n");	
	}

    printf("I have receive a message s_flag:%d\n",comb.s_flag);

	int index;

	switch(comb.s_flag)
	{
		case 11:
			if(comb.r_flag==1)
			{	
				printf("dui\n");
				return 1;
			}
			else
			{
				printf("cuo\n");
				return 0;
			}
			break;

		case 21:
			if(comb.r_flag==1)
			{
				printf("return id:%d name:%s pw:%s \n",comb.second_struct.id,comb.second_struct.name , comb.second_struct.passwd);
				return comb.second_struct.id;
			}
			else
				return -1;
			break;
//		case 41:
//		    if(comb.r_flag == 1)
///			 return 1;
//			 else return 0;
		case 53:
				printf("friend_list_hwnd:%d\n",friend_list_hwnd);
				if(getWinbyID(comb.third_struct.friend_id)==0)
				{
				
					pthread_t t1 , t2 ;
					setSelectUserID(comb.third_struct.friend_id);
					
					pthread_create(&t1, NULL, newWindow , NULL);
					pthread_create(&t2, NULL, waitCombine, NULL);
					
				}


				index=getIndexbyID(comb.third_struct.friend_id);
				printf("index:%d\n",index);
				
				strcat(id_win_chat[index].heSay,comb.third_struct.info);
				strcat(id_win_chat[index].heSay,"\n");
				
				printf("friend id:%d\n",comb.third_struct.friend_id);
				printf("get hdlg:%d\n",getWinbyID(comb.third_struct.friend_id));
			
				SetDlgItemText(getWinbyID(comb.third_struct.friend_id),IDC_CHAR_READ,id_win_chat[index].heSay);

				printf("**** %d say %s\n",comb.third_struct.user_id,comb.third_struct.info);
				save_info(comb);
				return 1;				
			break;
                   
	               case 72:
		  if(comb.r_flag == 1)
		    return 1;
	      else 
		    return 0;
			break;
		 case 61:
		   if(comb.r_flag == 1)
		             return 1;
		   else
		          return 0;
		  break;
	}
	
}


void * waitCombine(void *arg)
{
	while(1)
	{
		printf("****Begin Receive from Server****\n");
		COMBINE comb;
		classifyReceive(comb);
		printf("####End   Receive from Server####\n");
	}
}

void * pthreadInitFriendlist(void *arg)
{
	testDialogFriendlist(HWND_DESKTOP);
	//InitDialogBox2(HWND_DESKTOP);
}

void * newWindow(void *arg)
{
	InitDialogBox2(HWND_DESKTOP);

}

int checkPasswd(char *_id, char *_passwd)
{
	COMBINE comb;
	
	comb.first_struct.id=atoi(_id);
	strcpy(comb.first_struct.passwd,_passwd);
	comb.s_flag=11;

    setCurrentUserID(atoi(_id));
   
   
	printf("sockfd:%d\n",getSockfd());	
	
	if(sendto(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("checkpasswd send error\n");	
	}
	
	classifyReceive(comb);
}

int checkRegister(char *_name, char *_passwd, char *_passwd2, char *_gender, char *_age)
{
	if(strcmp(_passwd,_passwd2)!=0)
		return -2;


	COMBINE comb;

	comb.s_flag=21;
	comb.second_struct.age=atoi(_age);
	strcpy(comb.second_struct.name,_name);
	strcpy(comb.second_struct.passwd,_passwd);
	strcpy(comb.second_struct.gender,_gender);
	
	printf("sockfd:%d\n",getSockfd());	


	if(sendto(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("checkregister send error\n");	
	}

	return	classifyReceive(comb);
}
void sendChatText(int _user_id, int _friend_id, char *_chat_str)
{

	COMBINE comb;
	
	printf("##%d send to %d message: %s \n",_user_id,_friend_id,_chat_str);
	
	//comb.third_struct.user_id=atoi(_user_id);
	//comb.third_struct.friend_id=atoi(_friend_id);
	comb.third_struct.user_id=_user_id;
	comb.third_struct.friend_id=_friend_id;
	strcpy(comb.third_struct.info,_chat_str);
//	comb.third_struct.chat_time=_chat_time;
	
	comb.s_flag=53;

	if(sendto(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("sendChatText send error\n");	
	}

}

void printHwnd(HWND _hwnd)
{
	printf("ini _hwnd:%d\n",_hwnd);
}

void saveIDWin(int _id, HWND _hwnd)
{
	int i;i=0;
	while(id_win_chat[i].id!=0)
	{
		i++;
		if(i==20)
		{
			printf("open too many chat windows\n");
			break;
		}
	}
	id_win_chat[i].id=_id;
	id_win_chat[i].hwnd=_hwnd;
}

void deleteIDWin(int _hDlg)
{
	int i;i=0;
	while(id_win_chat[i].hwnd!=_hDlg)
	{
		i++;
		if(i==20)
		{
			printf("cannot delete id by hwnd\n");
			break;
		}
	}
	id_win_chat[i].id=0;
	id_win_chat[i].hwnd=0;
}

HWND getWinbyID(int _id)
{
	int i;i=0;
	while(id_win_chat[i].id!=_id)
	{
		i++;
		if(i==20)
		{
			printf("cannot find hwnd by id\n");
			break;
		}
	}
	return id_win_chat[i].hwnd;
}

int getIDbyWin(HWND _hwnd)
{
	int i;i=0;
	while(id_win_chat[i].hwnd!=_hwnd)
	{
		i++;
		if(i==20)
		{
			printf("cannot find id by hwnd\n");
			break;
		}
		
	}
	return id_win_chat[i].id;
}

int getIndexbyID(int _id)
{
	int i;i=0;
	while(id_win_chat[i].id!=_id)
	{
		i++;
		if(i==20)
		{
			printf("cannot find index by id\n");
			break;
		}
	}
	return i;
}

int getIndexbyWin(HWND _hwnd)
{
	int i;i=0;
	while(id_win_chat[i].hwnd!=_hwnd)
	{
		i++;
		if(i==20)
		{
			printf("cannot find index by hwnd\n");
			break;
		}
	}
	return i;
}


void justTest()
{	
	SetDlgItemText(getWinbyID(10001),IDC_CHAR_READ,"abdcddfdf");
}

void setCurrentUserID(int _id)
{
	current_user_id=_id;
}
int getCurrentUserID(void)
{
	return current_user_id;
}

 void checkUserInfo(COMBINE *comb)
 {
    
    comb->s_flag = 51;
   if(sendto(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr,sizeof(struct sockaddr)) < 0)
    {
      perror("checkUserInfo send error :");
    }
   if(recvfrom(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, &socket_len) < 0)
   {
     perror("checkUserInfo receive error:");
   }
 }
int checkUpdateInfo(int _id, char *_name, char *_passwd, char *_age, char *_gender)
 {
  COMBINE comb;
  comb.s_flag = 52;
  comb.second_struct.id = _id;
  comb.second_struct.age = atoi(_age);
  strcpy(comb.second_struct.name, _name);
  strcpy(comb.second_struct.passwd, _passwd);
  strcpy(comb.second_struct.gender, _gender);

 if(sendto(getSockfd(), &comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr,sizeof(struct sockaddr)) < 0)
  {
   perror("checkUpdateInfo send error:");
  }
 if(recvfrom(getSockfd(), &comb, sizeof(COMBINE), 0,(struct sockaddr*)&my_addr,&socket_len) < 0)
  {
   perror("checkUpdateInfo receive error:");
  }
  return comb.r_flag;
 }

 
 int checkFriendlist(COMBINE *comb)
 {
  comb->s_flag = 41;

	
 if(sendto(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0)
  {
    perror("checkFriendlist send error:");
  }
  
 if(recvfrom(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, &socket_len) < 0)
  {
    perror("checkFriendlist recive error:");
  }

  
  if(comb->r_flag == 0)
    return -1;
  else if(comb->r_flag == 1)
     return 1;
  else return 0;
  
 }
																					 
 int checkChatStart(int user_id, int friend_id)
 {
   COMBINE comb;
   comb.third_struct.user_id = user_id;
   comb.third_struct.friend_id = friend_id;
   if(sendto(getSockfd(), &comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr,sizeof(struct sockaddr)) < 0)
   {
     perror(" checkChatStart send error:");
  }
  if(recvfrom(getSockfd(), &comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, &socket_len) < 0)
  {
    perror("checkChatStart recive error:");
  }

    return 1;

 }
																 

int checkAlllist(COMBINE *comb)
{
  comb->s_flag = 71;
  if(sendto(getSockfd(),comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0)
  {
   perror("checkAlllist send error:");
  }
  if(recvfrom(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, &socket_len) < 0)
  {
   perror("checkAlllist recive error:");
  }
  if(comb->r_flag ==1)
     return 1;
  else 
    return 0;
}
void setSelectUserID(int _id)
{
  select_user_id = _id;
}
int getSelectUserID(void)
{
 return select_user_id;
}/*
int checkAddUserInfo(COMBINE *comb)
{
  comb->s_flag = 62;
  setSelectUserID(comb.second_struct.id);
 if(sendto(getSockfd(),comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0)
  {
   perror("checkAlllist send error:");
  }
   if(recvfrom(getSockfd(), comb, sizeof(COMBINE), 0, (struct sockaddr*)&my_addr, &socket_len) < 0)
  {
   perror("checkAlllist recive error:");
  }
   if(comb->r_flag ==1)
      return 1;
   else
     return 0;
											 
}

*/


int makeFriend(int my_id, int friend_id)
{
   COMBINE comb;
  comb.third_struct.user_id = my_id;
  comb.third_struct.friend_id = friend_id;
  comb.s_flag = 72;
 if(sendto(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0)
      {
         perror("makeFriend send error:");
	  }
 classifyReceive(comb);			   
}

int checkExit(int user_id)
{
  COMBINE comb;
  comb.s_flag = 61;
  comb.second_struct.id = user_id;
   if(sendto(getSockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0)
        {
         perror("makeFriend send error:");
     }
 classifyReceive(comb);


}




















