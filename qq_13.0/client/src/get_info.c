#include"client.h"

void   get_info(int  friend_id,unsigned char  buff[])
{
//	strcpy(buff,"\0");
	char tmp_str[4096];
	int read_len;
	FILE* open_file_type;
	int flag=1;
	
	char* chat_info_dir=NULL;
	size_t len;
	
	chat_info_dir=(char*)malloc(sizeof(char)*40);
	sprintf(chat_info_dir,"./chat_info/%d_%d",getCurrentUserID(),friend_id);
	
	if((open_file_type=fopen(chat_info_dir,"r"))==NULL)
	{
		perror("Open Wrong!/n Can`t find file");
		
	}
	char*  tmp_buf;
	size_t size;
//while(flag!=-1)
	
		read_len=getdelim(&tmp_buf,&len,'\t',open_file_type);
		read_len=getdelim(&tmp_buf,&len,'\t',open_file_type);
		tmp_buf=strtok(tmp_buf,"\t");
			
		if(read_len==-1)
		{
			flag=-1;
		}
	//	free(tmp_str);
		strcpy(tmp_str,tmp_buf);
	
		sprintf(tmp_buf,"#%s",tmp_str);
		if(flag==1&&(strlen(buff)+strlen(tmp_buf))!=4096)
		{
			strncat(buff,tmp_buf,strlen(tmp_buf));
		}
		 else if(flag==-1)
		 {
		 	printf("read record success\n");
		 }
		 else
		 {
			printf("the record file more than 4K or it`s NULL");
		 }
//	}
	
}

			  
