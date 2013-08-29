all:client.o get_info.o save_info.o

client.o:client.c
	gcc -c client.c -I ../inc
get_info.o:get_info.c
	gcc -c get_info.c  -I ../inc
save_info.o:save_info.c
	gcc -c save_info.c -I ../inc
clean::
	rm -rf *.o
