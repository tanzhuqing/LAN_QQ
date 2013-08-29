all:libmysql_connect.a server.out

libmysql_connect.a::
	@cd lib && $(MAKE)

mysql_connect.o:mysql_connect.c
	gcc -c mysql_connect.c -I ../inc


server.out::
	@cd src && $(MAKE)
clean::
	@cd src && $(MAKE) clean
