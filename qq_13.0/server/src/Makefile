VPATH1=/usr/local/mysql/lib/
VPATH2=/usr/local/mysql/include/
all:server.out
server.out:server.o deal_request.o
	gcc -o server.out server.o deal_request.o -L ../lib -lmysql_connect -L $(VPATH1) -lmysqlclient -lpthread
server.o:server.c
	gcc -c server.c -I ../inc -I $(VPATH2)
deal_request.o:deal_request.c
	gcc -c deal_request.c -I ../inc -I $(VPATH2)
clean:
	rm -rf *.o *.out
