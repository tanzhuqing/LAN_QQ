VPATH1=/usr/local/mysql/lib/
VPATH2=/usr/local/mysql/include/
all:libmysql_connect.a
libmysql_connect.a:mysql_connect.o
	ar rcs libmysql_connect.a mysql_connect.o
mysql_connect.o:mysql_connect.c
	gcc -c mysql_connect.c -I ../inc -I $(VPATH2)
clean:
	rm -rf *.o *.a
