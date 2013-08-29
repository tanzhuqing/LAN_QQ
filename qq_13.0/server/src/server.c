/*#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <mysql.h>*/

#include "deal_request.h"

#define MYPORT 4443
char 	abuf[256];//record the login user'IP
int 	UDP_sockfd,TCP_sockfd;
int main(int args,char **argv)
{
	/*Connect MySql*/
	MYSQL * mysql;
	MYSQL * conn_ret;
	mysql = (MYSQL *)malloc(sizeof(MYSQL));

	conn_ret = connectMysql(mysql,"192.168.1.200","root","123456","dingding_chatroom",3306,NULL,0);


	/*Connect Client*/

	struct sockaddr_in my_addr;
	socklen_t socket_len=sizeof(struct sockaddr);


	
	get_sockaddr(&my_addr,argv[1]);

	//init_TCP_sockfd();
	init_UDP_sockfd();

	bzero(&(my_addr.sin_zero),8);
/*		
	if(bind(get_TCP_sockfd(),(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind error\n");
		exit(1);
	}	*/
	
	if(bind(get_UDP_sockfd(),(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind error\n");
		exit(1);
	}
	
	pid_t pid;
	while(1)
	{
		pid=fork();
		if(pid<0)
		{
			perror("fork error\n");
		}
		if(pid==0)			/* child */
		{
		#if 0
			pthread_t t1,t2;
			int err;
			void *tret;
			
			err=pthread_create(&t1,NULL,listen_user,NULL);
			printf("erro:%d\n",err);
			err=pthread_create(&t2,NULL,UDP_service,mysql);
			printf("erro:%d\n",err);
		#endif
	#if 1	
			struct sockaddr_in addr;
			int count=0,s_count=0;
			COMBINE comb;

			count=recvfrom(get_UDP_sockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)abuf,&socket_len);
			const char * temp = (char *)inet_ntoa( ((struct sockaddr_in *)(abuf))->sin_addr.s_addr ); 
			
			printf("user port:%d\n",((struct sockaddr_in *)(abuf))->sin_port);
			
			strcpy(comb.first_struct.ip,temp) ;
			strcpy(comb.first_struct.real_ip,abuf);
			comb.first_struct.port=((struct sockaddr_in *)abuf)->sin_port;
			printf("%d\n",count);
			printf("login user IP:%s\n",inet_ntoa(((struct sockaddr_in *)(abuf))->sin_addr.s_addr));	
			
			if(count<0)
			{				
				perror("recv error");
				exit(1);
			}else{
			
				doRequest(mysql,&comb);
				printf("socked:%d\n",UDP_sockfd);	
				s_count=sendto(get_UDP_sockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)abuf,socket_len);
				printf("register id: %d\n",comb.second_struct.id);
			
			}
			#endif
		}else{				
			waitpid(pid,NULL,0);
		}
	}
	
	close(UDP_sockfd);
	
	return 0;
}

void get_sockaddr(struct sockaddr_in *addr,char *ip)
{
	addr->sin_family=AF_INET;	
	addr->sin_port=htons(MYPORT);
	addr->sin_addr.s_addr=inet_addr(ip);
}
int init_UDP_sockfd()
{
	UDP_sockfd=socket(AF_INET,SOCK_DGRAM,0);
}
int init_TCP_sockfd()
{
	TCP_sockfd=socket(AF_INET,SOCK_STREAM,0);
}
int get_UDP_sockfd()
{	
	return UDP_sockfd;
}
int get_TCP_sockfd()
{
	return TCP_sockfd;
}
#if 0
void * listen_user()
{
	socklen_t addrlen;
	struct sockaddr_in addr;
	int l_count;
	printf("i am in listen\n");	
		if(listen(TCP_sockfd,10)==0)
		{
			printf("*******\n");
		//	sleep(2);
			l_count=accept(get_TCP_sockfd(),(struct sockaddr *)&addr,&addrlen);	
		
			printf("l_count:%d\n",l_count);
				
		}
//		pthread_exit((void *)l_count);
		printf("i am out listen\n");
}
void * UDP_service(MYSQL *mysql)
{
	socklen_t socket_len=sizeof(struct sockaddr);
	struct sockaddr_in addr;
	int count=0,s_count=0;
	COMBINE comb;
	printf("I am in udp sevice\n");
	
	count=recvfrom(get_UDP_sockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)abuf,&socket_len);
	const char * temp = (char *)inet_ntoa( ((struct sockaddr_in *)(abuf))->sin_addr.s_addr ); 
		
	printf("user port:%d\n",((struct sockaddr_in *)(abuf))->sin_port);
			
	strcpy(comb.first_struct.ip,temp) ;			
	strcpy(comb.first_struct.real_ip,abuf);
	comb.first_struct.port=((struct sockaddr_in *)abuf)->sin_port;
	printf("%d\n",count);
	printf("login user IP:%s\n",inet_ntoa(((struct sockaddr_in *)(abuf))->sin_addr.s_addr));	
			
	if(count<0)
	{				
		perror("recv error");
		exit(1);
	}else{
	
		doRequest(mysql,&comb);
		printf("socked:%d\n",UDP_sockfd);	
		s_count=sendto(get_UDP_sockfd(),&comb,sizeof(COMBINE),0,(struct sockaddr*)abuf,socket_len);
		printf("register id: %d\n",comb.second_struct.id);
			
	}

//	pthread_exit(0);
}
#endif



