#include "mysql_connect.h"


MYSQL * connectMysql(MYSQL *mysql, const char *host, const char *user, const char *passwd ,const char *dbname, unsigned int port, const char *unix_socket,unsigned long client_flag)
{

	MYSQL * conn_ret;
	mysql_init(mysql);
	if((conn_ret=mysql_real_connect(mysql,host,user,passwd,dbname,port,unix_socket,client_flag))==NULL)
	{
		perror("Connect error\n");
		exit(1);
	}
	else{
		printf("Connect success\n");
	}

	return conn_ret;
}

MYSQL_RES* getResult(MYSQL *mysql,const char *query_str)
{
	int ret;
	MYSQL_RES *result=(MYSQL_RES *)malloc(sizeof(MYSQL_RES));

	ret=mysql_query(mysql,query_str);
	
	if(ret!=0)
	{
		perror("mysql_query error\n");
	}
	result=mysql_store_result(mysql);
	
	return result;
}

int addItem(MYSQL *mysql, const char *str)
{
	if(mysql_query(mysql,str))
	{
		printf("add item fail ,may be one has been added\n");
		return 0;
	}else
	{	
		printf("add item success\n");
		return 1;
	}
}

int  deleteItem(MYSQL *mysql, const char *str)
{
	if(mysql_query(mysql,str))
	{	
		printf("delete item fail\n");
		return 0;
	}
	else
	{
		printf("delete item success\n");
		return 1;
	}
}


void printResult(MYSQL_RES *result)
{
	MYSQL_ROW mysql_row;
	int fields;
	int rows;
	int i;
	
	fields	=mysql_num_fields(result);
	rows	=mysql_num_rows(result);

	printf("%d  results:\n",rows);
	if(rows)
	{
		while(mysql_row=mysql_fetch_row(result))
		{
			for(i=0;i<fields;++i)
			{
				printf("%s  ",mysql_row[i]);	
			}
			printf("\n");
		}
	}else
	{
		printf("Result has not found\n");
	}
}




