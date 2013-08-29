#include "deal_request.h"
//extern sockfd;
void doRequest(MYSQL *mysql, COMBINE *comb)
{
	int i;
	switch(comb->s_flag)
	{
	case 11:
		//if(checkPasswd(mysql,&comb->first_struct)==1)
		if(checkPasswd(mysql,&comb->first_struct)==1)
			comb->r_flag=1;
		else 
			comb->r_flag=0;
			break;
	case 21:
		if(checkRegister(mysql,&comb->second_struct)==1)
			comb->r_flag=1;
		else
			comb->r_flag=0;
			break;
	case 31:
		//checkChatRecord
			break;
	case 41:
		if(checkFriendList(mysql,comb->friend_list)==1)
			comb->r_flag=1;
		else
			comb->r_flag=0;
		//checkFriendList
			break;
	case 51:
		//Look user's info
		if(checkUserInfo(mysql,&comb->second_struct)==1)
		  comb->r_flag =1;
        else 
		   comb->r_flag=0;
			break;
	case 52:
		//modify user's info
		if(checkModifyInfo(mysql,&comb->second_struct)==1)
			comb->r_flag=1;
		else
			comb->r_flag=0;
			break;
	case 53:
		//user chat request
			//printf("&&&&&&&&&&&&\n");
		if(checkChatStart(mysql, &comb->third_struct)==1)
				comb->r_flag=1;
			else
				comb->r_flag=0;
		break;
	case 61:
			QQ_exit(mysql,&comb->second_struct);
		break;
	case 71:
		if(lookAllUser(mysql,comb->friend_list)==1)
			{
				 comb->r_flag=1;
			}
			else
			{
				 comb->r_flag=0;
			}
			break;
	case 72:
			#if 0 
			if(checkaddFriend(mysql,&comb->third_struct)==1)
				 comb->r_flag=1;
			else
				 comb->r_flag=0;
		    #endif
			if(addFriendValidate(mysql,comb)==1)
				 comb->r_flag=1;
			else
				 comb->r_flag=0;

			break;
	case 73:
		#if 0
			if(addFriendValidate(mysql,comb)==1)
				 comb->r_flag=1;
			else
				 comb->r_flag=0;
		#endif
			break;
	case 81:
			comb->r_flag=1;
		break;
	}
}
void QQ_exit(MYSQL *mysql,USER_INFO *user_info)
{
	char *update;
	MYSQL_RES *res;
	MYSQL_ROW my_row;
	int rows;
	update=(char *)malloc(sizeof(char)*40);
	res=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	
	sprintf(update,"update user set flag=0,ip=NULL,real_ip=NULL, port=NULL where id=%d ",user_info->id);
	mysql_query(mysql,update);


}
int checkPasswd(MYSQL *mysql, LOGIN_PACT *login_pact)
{
	char 		*query,*update;
	MYSQL_RES 	*rst,*u_res;
	int 		 rows;
	const char *temp=(char *)malloc(sizeof(char)*100);			
	query = (char *)malloc(sizeof(char)*100);
	update=	(char *)malloc(sizeof(char)*100);
	rst   = (MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	
	sprintf(query,"select * from user where id=%d and pwd='%s'",login_pact->id,login_pact->passwd);

	sprintf(update,"update user set flag=1 , ip='%s',port=%d,real_ip='%s' where id=%d",login_pact->ip,login_pact->port,(struct sockaddr *)login_pact->real_ip,login_pact->id);
	temp=(char *)inet_ntoa( ((struct sockaddr_in *)login_pact->real_ip)->sin_addr.s_addr ); 
	printf("login_user ip:%d\n",temp);
	printf("********\n");
	printf("%s\n",update);
	printf("@@@:%s\n",query);
	
	rst   = getResult(mysql,query);
	rows  = mysql_num_rows(rst);
	
	printf("%d\n",rows);
	if(rows>0)
	{
		if(mysql_query(mysql,update))
		{
			perror("update");
			
		}
		else
		{
			return 1;
		}
	}else
	{
		return 0;
	}
}

int checkRegister(MYSQL *mysql,USER_INFO *user_pact)
{
	char 		*insert,*query,*create_friendlist;
	int 		qq_id;
	int 		create_flag;
	qq_id	=return_qq_id(mysql);
	printf("QQ_id:%d\n",qq_id);
	insert	=(char *)malloc(100);
	query	=(char *)malloc(100);
	create_friendlist	=(char *)malloc(150);
	
	user_pact->id=qq_id;
	user_pact->flag=0;
	printf("insert into user values(%d,'%s',%d,'%s',%d,'%s')\n",user_pact->id,user_pact->passwd,user_pact->age,user_pact->gender,user_pact->flag,user_pact->name);

	sprintf(insert,"insert into user values(%d,'%s',%d,'%s',%d,'%s',NULL,NULL,NULL)",user_pact->id,user_pact->passwd,user_pact->age,user_pact->gender,user_pact->flag,user_pact->name);
	printf("insert:%s\n",insert);
   if(addItem(mysql,insert))
   {
		sprintf(create_friendlist,"CREATE TABLE %d_friend_list(id int AUTO_INCREMENT,friend_id int,primary key(id,friend_id))",qq_id);	
		printf("%s\n",create_friendlist);
		create_flag=mysql_query(mysql,create_friendlist);
		printf("create:%d\n",create_flag);
		
		return 1;
	}
	else
	{
		return 0;
	}

}
int checkFriendList(MYSQL *mysql, USER_INFO *friend_list)
{
	char *query;
	MYSQL_RES *res;
	MYSQL_ROW my_row;
	int user_id;
	int rows;
	int i=0;
	//int fields;
	
	query=(char *)malloc(sizeof(char)*150);
	res=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	user_id=friend_list[0].id;
	//maybe some problem in this statement
	sprintf(query,"select * from user , %d_friend_list  where %d_friend_list.friend_id=user.id  and user.flag=1 ",user_id,user_id);
	printf("friend_list query:%s\n",query);	
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	if(rows>0)
	{
		while(my_row=mysql_fetch_row(res))
		{	
			friend_list[i].id=atoi(my_row[0]);
			strcpy(friend_list[i].name,my_row[5]);
			printf("friend_id:%d friend_name:%s\n",friend_list[i].id,friend_list[i].name);
			i++;
		}
		return 1;
	}else
	{
		return 0;
	}
}
int checkChatRecord(MYSQL *mysql,CHAT_PACT *chat_pact)
{
	char *		insert;
	MYSQL_RES *	res;
	MYSQL_ROW my_row;
	char * my_time=(char *)malloc(40);
	insert	=(char *)malloc(sizeof(char)*40);
	insert	=(char *)malloc(sizeof(char)*40);
	res		=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	//printf("time:%d\n",time(t));
	//printf("%s\n",ctime(time(t)));
	getNowtime(my_time);
	printf("%s\n",my_time);
	//printf("time:%s\n",my_time);
	sprintf(insert,"insert into chat_info values(%d,%d,'%s','%s')",chat_pact->user_id,chat_pact->friend_id,my_time,chat_pact->info);
	
	if(addItem(mysql,insert))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
int checkUserInfo(MYSQL *mysql,USER_INFO *user_info)
{
	char *query;
	MYSQL_RES *res;
    MYSQL_ROW my_row;
	int rows;
	query=(char *)malloc(sizeof(char)*40);
	res=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));

	sprintf(query,"select * from user where id= %d ",user_info->id);
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	
	if(rows>0)
	{
		my_row=mysql_fetch_row(res);
		user_info->age=atoi(my_row[2]);
		strcpy(user_info->gender,my_row[3]);
		strcpy(user_info->name,my_row[5]);
		printf("user_name:%s\n",user_info->name);
		
		return 1;
	}else
	{
		return 0;
	}
	
}
int checkModifyInfo(MYSQL *mysql,USER_INFO *user_info)
{
	char *update;
	MYSQL_RES *res;
	MYSQL_ROW my_row;

	update=(char *)malloc(sizeof(char)*40);
	res=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	
	sprintf(update,"update user set pwd='%s' ,age=%d, gender='%s',name='%s' where id=%d ",user_info->passwd,user_info->age,user_info->gender,user_info->name,user_info->id);
	
	
	if(mysql_query(mysql,update))
	{
		return 0;
	}else
	{
		return 1;
	}

}
int checkChatStart(MYSQL *mysql, CHAT_PACT *chat_info)
{
	char *query;
	MYSQL_RES *res;
    MYSQL_ROW my_row;
	int rows;
	query=(char *)malloc(sizeof(char)*40);
	res=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));

	struct sockaddr_in my_addr;
	socklen_t sock_len=sizeof(struct sockaddr );
	int count;
	COMBINE chat_comb;
	char *my_time=(char *)malloc(sizeof(char)*30);
	char *info=(char *)malloc(sizeof(char)*2048);
	
	chat_comb.s_flag=53;
	chat_comb.third_struct.user_id=chat_info->friend_id;
	chat_comb.third_struct.friend_id=chat_info->user_id;
	//strcpy(chat_comb.third_struct.chat_time,chat_info->chat_time);
	sprintf(query,"select * from user where id= %d ",chat_info->user_id);
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	getNowtime(my_time);	
	if(rows>0)
	{	
		my_row=mysql_fetch_row(res);
		sprintf(info,"%s    %s\n%s",my_row[5],my_time,chat_info->info);
	}
	printf("%s\n",info);	
//	strcpy(chat_comb.third_struct.chat_time,chat_info->chat_time);
//	sprintf(info,"user_%s :\n%s",chat_info->info);
	strcpy(chat_comb.third_struct.info,info);
	strcpy(chat_info->info,info);
	//save the chatRecord
	checkChatRecord(mysql,chat_info);
	printf("user %d say to user %d that:%s\n",chat_info->user_id,chat_info->friend_id,chat_info->info);
	if(!get_UserIP(mysql,chat_info->friend_id,&my_addr))
	{
		printf("can not find the IP!\n");
		return 0;
	}
	
	printf("my_sockfd:%d\n",get_UDP_sockfd());	
	count=sendto(get_UDP_sockfd(),&chat_comb,sizeof(COMBINE),0,(struct sockaddr *)&my_addr,sock_len);
	printf("count:%d\n",count);
	perror("sendto :");
	if(count<0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int return_qq_id(MYSQL *mysql)
{ 
	char 		*query;
	MYSQL_RES 	*res,*res1;
	MYSQL_ROW 	row;
	int 		rows;
	int 		qq_id=10000;
	
	
	query	=(char *)malloc(100);
	
	while(1)
	{
		
		res		=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
		sprintf(query,"select * from user where id=%d",qq_id);
		res		=getResult(mysql,query);

		rows	=mysql_num_rows(res);
		if(rows>0)
		{
			 qq_id++;
		}else
		{
			return qq_id;
		}
	}

}
// if the r_flag is 72 use this function
int checkaddFriend(MYSQL *mysql, CHAT_PACT *chat_pact)
{
	COMBINE comb;
	struct sockaddr_in addr;
	socklen_t sock_len=sizeof(struct sockaddr );
printf("in addFriend\n");	
	comb.s_flag=73;
	comb.third_struct.user_id	=chat_pact->user_id;
	comb.third_struct.friend_id	=chat_pact->friend_id;
	strcpy(comb.third_struct.info,chat_pact->info);
	get_UserIP(mysql,chat_pact->friend_id,addr);
	
	if(sendto(get_UDP_sockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr *)&addr,sock_len)==-1)
	{
		perror("add friend error");
		return 0;
	}
	else
	{
		return 1;
	}
#if 0	
	//sprintf(query,"insert  from  ");
	sprintf(query,"select * from user where id=%d\n and flag=1",add_friend_id);
	printf("user_online query:%s\n",query);	
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);

	if(rows>0)
	{
			
	}
	else
	{
		return 0;
	}
	#endif
	
}

//if the friend send r_flag = 73 use this function
int addFriendValidate(MYSQL *mysql,COMBINE *comb)
{
	MYSQL_RES *res;
	int	rows;
	char *query;
	char *insert1,*insert2;
	struct sockaddr_in addr;
	
	socklen_t sock_len=sizeof(struct sockaddr);
	res		=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	insert1	=(char *)malloc(sizeof(char)*60);
	insert2	=(char *)malloc(sizeof(char)*60);
	query	=(char *)malloc(sizeof(char)*60);
	
	sprintf(query,"select * from %d_friend_list where friend_id=%d",comb->third_struct.user_id,comb->third_struct.friend_id);
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	
	if(rows>0)
		return 0;
	
//	if(comb->r_flag==1)
//	{
		//change the both friend_list tables;
		sprintf(insert1,"insert into %d_friend_list values(NULL,%d)",comb->third_struct.user_id,comb->third_struct.friend_id);
		sprintf(insert2,"insert into %d_friend_list values(NULL,%d)",comb->third_struct.friend_id,comb->third_struct.user_id);
		printf("insert 1:%s\n",insert1);
		printf("insert 2:%s\n",insert2);
		if(addItem(mysql,insert1)&&addItem(mysql,insert2))
		{
			
				return 1;
		//send success message to other user
		#if 0
			if(get_UserIP(mysql,comb->third_struct.friend_id,&addr)==1)
			{
				if(sendto(get_sockfd(),comb,sizeof(COMBINE),0,(struct sockaddr *)&addr,sock_len)==-1)
				{
					perror("sendto");
				}
				return 1;
			}
			else
			{
				printf("can not find IP!\n");
				return 0;
			}
		#endif
		}
		else
		{
			return 0;
		}
//	}
//	return 0;
}

int lookAllUser(MYSQL *mysql, USER_INFO *friend_list)
{
	char *query;
	MYSQL_RES *res;
	MYSQL_ROW my_row;
	int user_id;
	int rows;
	int i=0;

	
	query	=(char *)malloc(sizeof(char)*150);
	res		=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	user_id	=friend_list[0].id;
	query="select * from user where flag=1";
	
	printf("All user query:%s\n",query);	
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	if(rows>0)
	{
		while(my_row=mysql_fetch_row(res))
		{	
			friend_list[i].id	=atoi(my_row[0]);
			strcpy(friend_list[i].name,my_row[5]);
			friend_list[i].flag	=atoi(my_row[4]);
			printf("user  id:%d user name:%s\n",friend_list[i].id,friend_list[i].name);
			i++;
		}
		
		for(i;i<30;i++)
		{
			friend_list[i].id	=0;
			strcpy(friend_list[i].name," ");
		}
		return 1;
	}else
	{
		return 0;
	}
	
}

int  get_UserIP(MYSQL *mysql, int id,struct sockaddr_in *addr)
{
	MYSQL_RES *res;
	MYSQL_ROW  row;
	
	res					=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));
	char *query			=(char *)malloc(sizeof(char)*100);
	char *char_ip		=(char *)malloc(sizeof(char)*200);
	socklen_t sock_len	=sizeof(struct sockaddr );
	int rows;
	int port;
	printf("in get_ip\n");	
    	
	sprintf(query,"select * from user where id=%d",id);
	res=getResult(mysql,query);
	rows=mysql_num_rows(res);
	if(rows>0)
	{
		row=mysql_fetch_row(res);
	//	printf("vvvvvvvvvvvvv\n");
		printf("row:%s\n",row[8]);
		port=atoi(row[8]);
	///	printf("@@@@@@@\n");
		printf("my_port:%d\n",port);
  		addr->sin_family=AF_INET;
		addr->sin_port=port;
		addr->sin_addr.s_addr=inet_addr(row[6]);
		printf("user iP:%s\n",row[6]);
		return 1;
	}
	else
	{
		return 0;
	}
}
void getNowtime(char *my_time)
{
	time_t t;
	struct tm *my_tm;

	time(&t);

	my_tm=gmtime(&t);
	
	sprintf(my_time,"%d-%d-%d %d:%d:%d",(my_tm->tm_year+1900),my_tm->tm_mon+1,my_tm->tm_mday,my_tm->tm_hour+8,my_tm->tm_min,my_tm->tm_sec);
}

