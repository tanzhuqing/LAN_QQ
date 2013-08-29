#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdarg.h>
#include"client.h"


#include<minigui/common.h>
#include<minigui/minigui.h>
#include<minigui/gdi.h>
#include<minigui/window.h>
#include<minigui/mywindows.h>
#include<minigui/control.h>




#define IDC_CHOOSED 1101
#define IDC_STARTCHAT 1102
#define IDC_FRIENDLIST 1103
#define IDC_SYSMANAGE 1104
#define IDC_INFOID 1105
#define IDC_INFONAME 1106
#define IDC_INFOAGE 1107
#define IDC_INFOPWD 1108
#define IDC_INFOGENDER 1109
#define IDC_MODIFY 1110
#define IDC_ADDFRIEND 1111
#define IDC_ADDFRIENDLIST 1112
#define IDC_FINFOID 1113
#define IDC_FINFOAGE 1114
#define IDC_FINFONAME 1115
#define IDC_FINFOGENDER 1116
#define IDC_FADD 1117
#define IDC_FINFO 1118
#define IDC_SYSMODIFY 1119
#define  IDC_FDELETE 1120
#define  IDC_REFRESH 1121
void testDialogSysManage(HWND hwnd);
void testDialogModifyInfo(HWND hwnd);
void testDialogAllUserInfo(HWND hwnd); 
void testDialogSysModify(HWND hwnd);


static DLGTEMPLATE DlgFriendlist =
  {
  WS_BORDER | WS_CAPTION,
  WS_EX_NONE,
  520, 100, 250, 420,
  "My friend list ",
  0,0,
  6,NULL,
  0
 };
											  
static CTRLDATA CtrlFriendlist[] =
 {
    {
    "static",
    WS_VISIBLE |WS_TABSTOP,
    20,10,200,20,
    IDC_STATIC,
    "Double click to chat: ",
    0
    },
	{
	 "button",
	 WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
	 150,10,40,20,
	 IDC_REFRESH,
	 "refresh",
	 0
	},
	{
	  "button",
	  WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
	  200,10,40,20,
	  IDC_ADDFRIEND,
	  "add",
	  0
	},
   {
    "listbox",
   WS_BORDER | WS_CHILD |WS_VISIBLE |WS_VSCROLL |WS_HSCROLL|LBS_SORT|LBS_NOTIFY,
   20,40,200,280,
   IDC_FRIENDLIST,
   "",
    0
    },
   {
   "button",
    WS_VISIBLE |WS_CHILD |BS_PUSHBUTTON,
    30,350,100,20,
    IDC_SYSMANAGE,
    "Sysmanage",
     0
   },
   {
   "button",
   WS_VISIBLE |BS_PUSHBUTTON |WS_TABSTOP,
   140,350,80,20,
   IDCANCEL,
   "exit",
   0
   }

 };
static  DLGTEMPLATE DlgUserInfo =
 {
  WS_BORDER | WS_CAPTION,
  WS_EX_NONE,
  300,270,200,250,
  "Modify my information ",
  0,0,
  12,NULL,
  0
 };
static CTRLDATA CtrlUserInfo[] =
 {
   {
   "static",
   WS_VISIBLE |SS_LEFT,
   10,10,80,20,
   IDC_STATIC,
   "id:",
   0
   },
   {
   "static",
   WS_VISIBLE |WS_TABSTOP,
   60,10,80,20,
   IDC_INFOID,
   NULL,
   0
  },
  {
   "static",
   WS_VISIBLE|SS_LEFT,
   10,40,80,20,
   IDC_STATIC,
   "name:",
    0
  },
  {
   "edit",
   WS_VISIBLE|WS_TABSTOP,
   60,40,80,20,
   IDC_INFONAME,
    NULL,
    0
   },
   {
   "static",
    WS_VISIBLE|SS_LEFT,
    10,70,80,20,
    IDC_STATIC,
   "password:",
   0
   },
   {
   "edit",
   WS_VISIBLE|WS_TABSTOP,
   60,70,80,20,
   IDC_INFOPWD,
   NULL,
   0
   },
   {
   "static",
   WS_VISIBLE|SS_LEFT,
   10,100,80,20,
   IDC_STATIC,
   "age:",
   0
   },
   {
    "edit",
    WS_VISIBLE|WS_TABSTOP,
    60,100,80,20,
    IDC_INFOAGE,
    NULL,
    0
	 },
	 {
	  "static",
	   WS_VISIBLE|SS_LEFT,
	   10,130,80,20,
	   IDC_STATIC,
	    "gender:",
	   0
	  },
	  {
	   "edit",
	   WS_VISIBLE|WS_TABSTOP,
	    60,130,80,20,
	    IDC_INFOGENDER,
	   NULL,
	    0
	   },
	  {
	  "button",
	   WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
	   10,180,60,20,
	    IDC_MODIFY,
	    "modify",
	   0
	  },
      {
       "button",
       WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
       110,180,60,20,
	   IDCANCEL,
	  "cancel",
	   0
	  }
 };
 static DLGTEMPLATE DlgAddFriend =
 {
  WS_BORDER|WS_CAPTION,
  WS_EX_NONE,
  300,100,200,320,
  "Online users ",
  0,0,
  3,NULL,
  0
 };
 static CTRLDATA CtrlAddFriend[]=
 {
     {
    "static",
	WS_VISIBLE,
	10,10,220,20,
	IDC_STATIC,
	"Double click a user to check info",
	0
   },
  {
   "listbox",
   WS_BORDER | WS_CHILD |WS_VISIBLE |WS_VSCROLL |WS_HSCROLL|LBS_SORT|LBS_NOTIFY,
   17,30,160,220,
   IDC_ADDFRIENDLIST,
   NULL,
    0
	},

	{
	"button",
	WS_VISIBLE,
	120,260,60,20,
	IDCANCEL,
	"cancel",
	0
	}
 };   
 
 static  DLGTEMPLATE DlgAllUserInfo =
  {
   WS_BORDER | WS_CAPTION,
   WS_EX_NONE,
   100,200,200,220,
   "Information ",
   0,0,
   10,NULL,
   0
  };
 static CTRLDATA CtrlAllUserInfo[] =
  {
    {
    "static",
    WS_VISIBLE |SS_LEFT,
    10,10,80,20,
    IDC_STATIC,
    "id:",
    0
  },
  {
    "static",
   WS_VISIBLE |WS_TABSTOP,
    60,10,80,20,
    IDC_FINFOID,
    NULL,
   0
   },
   {
   "static",
    WS_VISIBLE|SS_LEFT,
    10,40,80,20,
    IDC_STATIC,
    "name:",
    0
   },
     {
   "static",
   WS_VISIBLE|WS_TABSTOP,
   60,40,80,20,
   IDC_FINFONAME,
     NULL,
     0
    },
  
  {
   "static",
   WS_VISIBLE|SS_LEFT,
   10,70,80,20,
   IDC_STATIC,
    "age:",
   0
   },
   {
     "static",
     WS_VISIBLE|WS_TABSTOP,
     60,70,80,20,
     IDC_FINFOAGE,
     NULL,
    0
      },
     {
      "static",
       WS_VISIBLE|SS_LEFT,
       10,100,80,20,
        IDC_STATIC,
        "gender:",
      0
       },
       {
        "static",
        WS_VISIBLE|WS_TABSTOP,
        60,100,80,20,
        IDC_FINFOGENDER,
        NULL,
      0
     },
   {
     "button",
      WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
      10,150,60,20,
      IDC_FADD,
     "add friend",
     0
    },
	 {
	     "button",
	      WS_VISIBLE|BS_PUSHBUTTON|WS_TABSTOP,
	      110,150,60,20,
	      IDCANCEL,
	      "cancel",
	       0
	     }
  };
									   

 static void Alllist_notif_proc(HWND hwnd,int id,int nc,DWORD add_data)
  {
   if(nc == LBN_DBLCLK)
    {
      //int count = SendMessage(hwnd,LB_GETSELCOUNT,0,0L);
       int index = SendMessage(hwnd,LB_GETCURSEL,0,0L);

        char buffer[20];
        char *id;
        SendMessage(hwnd,LB_GETTEXT,index,(LPARAM)buffer);
        strtok(buffer,"(");
        id=strtok(NULL,")");
        id = strtok(id,"(");
        printf("doule click id =%s\n",id);
        int chat_id = atoi(id);
        setSelectUserID(chat_id); 
        testDialogAllUserInfo(HWND_DESKTOP);
        id = NULL;
      }
  }
																				 

  static void list_notif_proc(HWND hwnd,int id,int nc,DWORD add_data)
  {
  		if(nc == LBN_DBLCLK)
		{
	  //int count = SendMessage(hwnd,LB_GETSELCOUNT,0,0L);
	  		int index = SendMessage(hwnd,LB_GETCURSEL,0,0L); 
	    	char buffer[20];
			char *id;
	    	SendMessage(hwnd,LB_GETTEXT,index,(LPARAM)buffer);
	   		strtok(buffer,"(");
			id=strtok(NULL,")");
			id = strtok(id,"(");
			printf("doule click id =%s\n",id);          
        	int chat_id = atoi(id); 
			checkChatStart(getCurrentUserID(),chat_id);/////////////////
	    	
		/********* by guan ********/

			setSelectUserID(chat_id); 
			printf("[current:%d, select:%d]\n",getCurrentUserID(),getSelectUserID());
			printf("[getWinbyID( %d )]:%d\n",chat_id,getWinbyID(chat_id));
		
			if(getWinbyID(chat_id)==0)
			{
				InitDialogBox2(HWND_DESKTOP);
				id = NULL;
			}

		/***************************/
	   
	   }
		
   }
 static int DialogAddFriend(HWND hwnd,int message, WPARAM wParam, LPARAM lParam)
 {
   switch(message){
       case MSG_INITDIALOG:
       {
	     COMBINE com;
		 int k;
		 int i;
		 i = 0;
		 char b[30];
		 switch(k = checkAlllist(&com))
	     {
		   case 0:
		        MessageBox(hwnd,"Friend Access Fail!","",MB_OK);
			    break;
			case 1:
			  {
			    while(com.friend_list[i].id != 0)
			         {
			             sprintf(b,"%s (%d)",com.friend_list[i].name,com.friend_list[i].id);
			          printf("id = %d name = %s\n",com.friend_list[i].id,com.friend_list[i].name);
			               SendDlgItemMessage(hwnd, IDC_ADDFRIENDLIST, LB_ADDSTRING, 0, (LPARAM)b);
			              i++;
			           }
			            SetNotificationCallback(GetDlgItem(hwnd,IDC_ADDFRIENDLIST),Alllist_notif_proc);
			       break;
					
		 
		        }
         
		 // char b[20]="test (10001)";
		 // SendDlgItemMessage(hwnd, IDC_ADDFRIEND, LB_ADDSTRING, 0, (LPARAM)b);
		  
   	     }
        return 1;
		}
	   case MSG_COMMAND:
	   switch(wParam){
	       case  IDCANCEL:
	        EndDialog(hwnd,wParam);
		    break;
		}
		break;
   }
   return DefaultDialogProc(hwnd,message,wParam,lParam);
 }
void testDialogAddfriend(HWND hwnd)
{
 DlgAddFriend.controls = CtrlAddFriend;
 DialogBoxIndirectParam(&DlgAddFriend,hwnd,DialogAddFriend,0L);
}
  

static int DialogFriendlist(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{

  switch(message){ 
  case MSG_INITDIALOG:
    {
	   COMBINE com;
	   com.friend_list[0].id = getCurrentUserID();
    
//by guan

friend_list_hwnd=hwnd;
//

		int j,i;
		char buff[30];
		switch(j=checkFriendlist(&com))//////////////
		{
		 case 0:
		 	MessageBox(hwnd,"Friend Access Fail !","",MB_OK);
			break;
		 case -1:
		 	MessageBox(hwnd,"No online Friends !","",MB_OK);
			break;
		  default:
		    i = 0;
		   while(com.friend_list[i].id != 0)
		  {
		       sprintf(buff,"%s    ( %d )",com.friend_list[i].name,com.friend_list[i].id);
		       printf("id = %d name = %s\n",com.friend_list[i].id,com.friend_list[i].name);
		       SendDlgItemMessage(hwnd, IDC_FRIENDLIST, LB_ADDSTRING, 0, (LPARAM)buff);
	 	       i++;  
		    }
			 SetNotificationCallback(GetDlgItem(hwnd,IDC_FRIENDLIST),list_notif_proc);
			break;
		}	
	}
	return 1;
 
  
  case MSG_COMMAND:
  	switch(wParam){
	case IDC_SYSMANAGE:
         testDialogSysModify(HWND_DESKTOP);        
	    break;
	case IDC_ADDFRIEND:
	    testDialogAddfriend(HWND_DESKTOP);
	    break;
	 case IDC_REFRESH:
	 {
      SendMessage(GetDlgItem(hwnd,IDC_FRIENDLIST),LB_RESETCONTENT,0,0);
       COMBINE com;
	   com.friend_list[0].id = getCurrentUserID();
	    int j,i;
	   char buff[30];
	   switch(j=checkFriendlist(&com))//////////////
	       {
	         case 0:
	            MessageBox(hwnd,"Friend Access Fail !","",MB_OK);
	             break;
	        case -1:
	            MessageBox(hwnd,"No online Friends !","",MB_OK);
		            break;
		     default:
		       i = 0;
		       while(com.friend_list[i].id != 0)
		      {
		            sprintf(buff,"%s (%d)",com.friend_list[i].name,com.friend_list[i].id);
		      printf("id = %d name = %s\n",com.friend_list[i].id,com.friend_list[i].name);
		              SendDlgItemMessage(hwnd, IDC_FRIENDLIST, LB_ADDSTRING, 0, (LPARAM)buff);
		               i++;
		        }
		   SetNotificationCallback(GetDlgItem(hwnd,IDC_FRIENDLIST),list_notif_proc);
		       break;
		      }
        }
        break;
	case IDCANCEL:
                checkExit(getCurrentUserID());
		EndDialog(hwnd,wParam);
		break;
	}
	break;
  }
  return DefaultDialogProc(hwnd,message,wParam,lParam);
}

DialogSysModify(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{
  switch(message){
  case MSG_INITDIALOG:
 
    {
	COMBINE com;
	com.second_struct.id = getCurrentUserID();
   checkUserInfo(&com);
  char mid[20];
  char mage[20];
   sprintf(mid,"%d",com.second_struct.id);
   sprintf(mage,"%d",com.second_struct.age);
 printf("age = %d\n",com.second_struct.age);
 SetDlgItemText(hwnd,IDC_INFOID,mid);
 SetDlgItemText(hwnd,IDC_INFONAME,com.second_struct.name);	
 SetDlgItemText(hwnd,IDC_INFOPWD,com.second_struct.passwd);
 SetDlgItemText(hwnd,IDC_INFOAGE,mage);
 SetDlgItemText(hwnd,IDC_INFOGENDER,com.second_struct.gender);
  
  return 1;
  }
  case MSG_COMMAND:
  	switch(wParam){
	case IDC_MODIFY:
	       {
		         char buff_name[20];
		         char buff_passwd[20];
		         char buff_age[4];
		         char buff_gender[20];
		         GetWindowText(GetDlgItem(hwnd,IDC_INFONAME),buff_name,20);
		         GetWindowText(GetDlgItem(hwnd,IDC_INFOPWD),buff_passwd,20);
		         GetWindowText(GetDlgItem(hwnd,IDC_INFOAGE),buff_age,4);
		         GetWindowText(GetDlgItem(hwnd,IDC_INFOGENDER),buff_gender,4);
		         printf("name = %s,pwd = %s,age = %s,gender= %s\n",buff_name,buff_passwd,buff_age,buff_gender);
		         int i;
		        
		     switch(i=checkUpdateInfo(getCurrentUserID(),buff_name,buff_passwd,buff_age,buff_gender))
		       {
			         case 0:
			            MessageBox(hwnd,"Modify Fail!","Fail",MB_OK);
			          break;
			        case 1:
			            MessageBox(hwnd,"Modify Success!","Success",MB_OK);
				      EndDialog(hwnd,wParam);
				   
				   break;
				 }
	       }
		
		break;
	case IDCANCEL:
		EndDialog(hwnd,wParam);
		break;
	}
	break;
  }
return DefaultDialogProc(hwnd,message,wParam,lParam);
}
DialogAllUserInfo(HWND hwnd ,int message ,WPARAM wParam,LPARAM lParam)
{
  switch(message)
  {
   case MSG_INITDIALOG:
       {
           COMBINE com;
	       com.second_struct.id = getSelectUserID();
		   checkUserInfo(&com);
		   char mid[20];
		   char mage[20];
		   sprintf(mid,"%d",com.second_struct.id);
		   sprintf(mage,"%d",com.second_struct.age);
		   printf("age = %d\n",com.second_struct.age);
		  SetDlgItemText(hwnd,IDC_FINFOID,mid);
		  SetDlgItemText(hwnd,IDC_FINFONAME,com.second_struct.name);
		  SetDlgItemText(hwnd,IDC_FINFOAGE,mage);
		  SetDlgItemText(hwnd,IDC_FINFOGENDER,com.second_struct.gender); 
       return 1;
	   }
	case MSG_COMMAND:
	  switch(wParam)
         {
		 case IDC_FADD:
		 {
	               int friend_id,k; 
			char buff_id[20];
		    GetWindowText(GetDlgItem(hwnd,IDC_FINFOID),buff_id,20);
			friend_id = atoi(buff_id);
		   switch(k=makeFriend(getCurrentUserID(),friend_id))
		   {
		    case 1:
			  MessageBox(hwnd,"Add Success !","Success",MB_OK);
			  EndDialog(hwnd,wParam);
			  break;
		    case 0:
			  MessageBox(hwnd,"Add Failure !","Failure",MB_OK);
			  break;
		   }
		 
		 }
		  break;
		 case IDCANCEL:
		     EndDialog(hwnd,wParam);
		     break;
        }
    break;
  }
 return DefaultDialogProc(hwnd,message,wParam,lParam);
}
void testDialogAllUserInfo(HWND hwnd)
{
 DlgAllUserInfo.controls = CtrlAllUserInfo;
 DialogBoxIndirectParam(&DlgAllUserInfo,hwnd,DialogAllUserInfo,0L);
}
void testDialogSysModify(HWND hwnd)
{
  DlgUserInfo.controls = CtrlUserInfo;
  DialogBoxIndirectParam(&DlgUserInfo, hwnd,DialogSysModify,0L);
}

void testDialogFriendlist(HWND hwnd)
{
   DlgFriendlist.controls = CtrlFriendlist;
   DialogBoxIndirectParam(&DlgFriendlist,hwnd,DialogFriendlist,0L); 
}

#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif
		
