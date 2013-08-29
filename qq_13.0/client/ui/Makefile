all:client.o  get_info.o save_info.o login_win.out 

client.o::
	cd ../src && $(MAKE)
get_info.o::
	cd ../src && $(MAKE)
save_info.o::
	cd ../src && $(MAKE)
login_win.out:login_win.o ../src/client.o register_win.o ui_chat_record.o chat_win.o friendlist_win.o progressbar_win.o ../src/get_info.o ../src/save_info.o

#<<<<<<< Makefile

#login_win.out:login_win.o ../src/client.o register_win.o chat_win.o
#	gcc -o login_win.out login_win.o ../src/client.o register_win.o chat_win.o -lpthread  -lminigui -ljpeg -lpng -lz 
#=======
	gcc -o login_win.out login_win.o ../src/client.o ../src/get_info.o ../src/save_info.o  register_win.o ui_chat_record.o chat_win.o  friendlist_win.o progressbar_win.o -lpthread  -lminigui -ljpeg -lpng -lz
#>>>>>>> 1.4
login_win.o:login_win.c
	gcc -c login_win.c -I ../inc
chat_win.o:chat_win.c
	gcc -c chat_win.c -I ../inc
register_win.o:register_win.c
	gcc -c register_win.c -I ../inc

#get_info.o:get_info.c
#	gcc -c get_info.c -I ../inc
#save_info.o:save_info.c
#	gcc -c save_info.c -I ../inc
ui_chat_record.o:ui_chat_record.c
	gcc -c ui_chat_record.c  -I ../inc
friendlist_win.o:friendlist_win.c
	gcc -c friendlist_win.c -I ../inc
progressbar_win.o:progressbar_win.c
	gcc -c progressbar_win.c -I ../inc
clean:
	rm -rf *.o *.out rm -rf ../src/*.o
	
#ui_chat_record.o:ui_chat_record.c
#	gcc -c ui_chat_record.c
