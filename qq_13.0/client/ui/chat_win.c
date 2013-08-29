#include "client.h"
#include "qq_ui.h"

static DLGTEMPLATE DlgInitProgress2=
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0,0,363,430,
	"DINGDING_CHAT",
	0,0,
	4,NULL,
	0
};

//#define IDC_CHAR_READ 300
//#define IDC_CHAR_WRITE 400

static CTRLDATA CtrlInitProgress2[]=
{
	{
		CTRL_TEXTEDIT,
		WS_CHILD | WS_VISIBLE |WS_BORDER | ES_READONLY | ES_AUTOWRAP | WS_HSCROLL | WS_VSCROLL,
		20,20,320,250,
		IDC_CHAR_READ,
		NULL,
		0
	},
	{
		CTRL_TEXTEDIT,
		WS_CHILD | WS_VISIBLE |WS_BORDER | ES_AUTOWRAP | WS_HSCROLL |WS_VSCROLL,
		20,280,320,80,
		IDC_CHAR_WRITE,
		NULL,
		0
	},

	{
	   "button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100,370,56,23,
		IDRECORD,
		"RECORD",
			0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		290,370,50,23,
		IDOK,
		"Send",
		0
	}
};

static int InitDialogBoxProc2(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	char buff_id[20];
	char buff_r [4096];
	char buff_w [4096];
	int  index;

	
	switch(message)
	{
		case MSG_INITDIALOG:
			saveIDWin(getSelectUserID(),hDlg);

			sprintf(buff_id,"chat %d ^_^",getSelectUserID());
			SendMessage(hDlg,MSG_SETTEXT,20,(LPARAM)buff_id);
			printf("inidlg:%d\n",getWinbyID(getSelectUserID()));
			printf("id_win_chat[0]- id:%d - hwnd:%d \n",id_win_chat[0].id,id_win_chat[0].hwnd);
			//saveIDWin(10001,hDlg);
			return 1;

		/*case MSG_KEYDOWN:
			switch(wParam)
			{
			case KS_SHIFT:
				printf("###\n");
				break;
			}
			return 0;
		*/
		case MSG_COMMAND:
			switch(wParam)
			{
				case IDOK:
				{
					GetDlgItemText (hDlg,IDC_CHAR_WRITE,buff_w,1024);
					buff_w[1024]='\0';
					printf("<< UserID:%d , FriendID:%d >>\n",getCurrentUserID(),getIDbyWin(hDlg));
					sendChatText(getCurrentUserID(),getIDbyWin(hDlg),buff_w);
		
					memset(buff_r,'\0',sizeof(buff_r));
					SetDlgItemText(hDlg,IDC_CHAR_WRITE,buff_r);
				 break;
				}
				case IDRECORD:
					{
						InitDialogBox3(HWND_DESKTOP,hDlg);
						break;
					}
			}
			break;
			case MSG_CLOSE:
			
			index=getIndexbyWin(hDlg);
			memset(id_win_chat[index].heSay,'\0',sizeof(id_win_chat[index].heSay));
			
			deleteIDWin(hDlg);
			EndDialog(hDlg, IDCANCEL);
			break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

void InitDialogBox2(HWND hWnd)
{
	
	DlgInitProgress2.controls=CtrlInitProgress2;
	DialogBoxIndirectParam (&DlgInitProgress2, hWnd, InitDialogBoxProc2, 0L);
}


#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif


