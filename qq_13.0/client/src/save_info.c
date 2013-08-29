#include"client.h"

void  save_info(COMBINE tags)
{
int  file_type;
char* file_info_dir;
mode_t mode=0744;
char* chat_tmp=NULL;
file_info_dir=(char*)malloc(20*sizeof(char));
chat_tmp=(char*)malloc(1024*sizeof(char));

sprintf(file_info_dir,"chat_info/%d_%d",getCurrentUserID(),(tags.third_struct).friend_id);
printf("%s\n",file_info_dir);
file_type=open(file_info_dir,O_CREAT|O_RDWR|O_TRUNC,mode);
if(file_type==-1)
{
	file_type=open(file_info_dir,O_APPEND|O_RDWR,mode);
}
printf("dddddddddddddddddddddddd\n%d",file_type);

sprintf(chat_tmp,"\t%s",(tags.third_struct).info);
	 write(file_type,chat_tmp,strlen(chat_tmp));
}
										   
