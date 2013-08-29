#ifndef _CONNECT_MYSQL_H
#define _CONNECT_MYSQL_H
#include <stdio.h>
#include <errno.h>
#include <mysql.h>
#include <stdlib.h>
#include <time.h>


MYSQL *  connectMysql(MYSQL *mysql, const char *host, const char *user, const char *passwd ,const char *dbname, unsigned int port, const char *unix_socket,unsigned long client_flag);

MYSQL_RES* getResult(MYSQL *mysql,const char *query_str);

int addItem(MYSQL * , const char *);

int deleteItem(MYSQL * , const char *);

void printResult(MYSQL_RES *mysql_res);


#endif

