/*#include <stdio.h> 
 
#include <minigui/common.h> 
#include <minigui/minigui.h> 
#include <minigui/gdi.h> 
#include <minigui/window.h> 
#include <minigui/control.h>

void InitDialogBox(HWND hwnd);
*/
#include "client.h"
#include "qq_ui.h"


static DLGTEMPLATE DlgInitProgress1=
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	350,100,240,340,
	"REGISTER",
	0,0,
	13,NULL,
	0
};
#define IDC_CHAR_NAME 100
#define IDC_CHAR_PASSWD 101
#define IDC_CHAR_PASSWD2 102
#define IDC_CHAR_GENDER 103
#define IDC_CHAR_AGE 104
#define IDREGSTER 201

static CTRLDATA CtrlInitProgress1[]=
{
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE ,
		60,40,160,20,
		IDC_STATIC,
		"Thanks for registering",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,80,60,20,
		IDC_STATIC,
		"Name",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,110,60,20,
		IDC_STATIC,
		"Passwd",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,140,60,20,
		IDC_STATIC,
		"rePasswd",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,170,60,20,
		IDC_STATIC,
		"Gender",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,200,60,20,
		IDC_STATIC,
		"Age",
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,80,100,20,
		IDC_CHAR_NAME,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,110,100,20,
		IDC_CHAR_PASSWD,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,140,100,20,
		IDC_CHAR_PASSWD2,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,170,100,20,
		IDC_CHAR_GENDER,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,200,100,20,
		IDC_CHAR_AGE,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		45,270,60,30,
		IDOK,
		"Submit",
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		140,270,60,30,
		IDCANCEL,
		"Cancel",
		0
	}
};

static int InitDialogBoxProc1(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	

	switch(message)
	{
		case MSG_INITDIALOG:
	/*	printHwnd(hDlg);
		saveIDWin(10001,hDlg);
		HWND minihwnd;
		minihwnd=getWinbyID(10001);
	*/	
			return 1;

		case MSG_COMMAND:
			switch(wParam)
			{
				case IDOK:
				{

					connect_server();

					char buff_name 		[20];
					char buff_passwd 	[40];
					char buff_passwd2	[40];
					char buff_gender	[4];
					char  buff_age		[4];
				
					memset(buff_name,'\0',sizeof(buff_name));
					memset(buff_passwd,'\0',sizeof(buff_passwd));
					memset(buff_passwd2,'\0',sizeof(buff_passwd2));
					memset(buff_gender,'\0',sizeof(buff_gender));
					memset(buff_age,'\0',sizeof(buff_age));
				
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR_NAME),buff_name,20);
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR_PASSWD),buff_passwd,40);
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR_PASSWD2),buff_passwd2,40);
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR_GENDER),buff_gender,4);
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR_AGE),buff_age,4);
					
					int i;
					char *out_str;
					out_str=(char *)malloc(50);
					
					switch(i=checkRegister(buff_name,buff_passwd,buff_passwd2,buff_gender,buff_age))
					{
					case -1:
						MessageBox (hDlg,"Register Fail","- -|",MB_OK);
						break;
					case -2:
						MessageBox (hDlg,"Passwd different","- -|",MB_OK);
						break;
					default:
						sprintf(out_str,"Register Success\nYour ID :%d",i);
						MessageBox (hDlg,out_str,"^_^",MB_OK);
						free(out_str);
						break;
					}
				}
				break;
				case IDCANCEL:
					EndDialog(hDlg, wParam);
					//InitDialogBox(HWND_DESKTOP);
					break;
			}
			break;
		case MSG_CLOSE:
			EndDialog(hDlg, IDCANCEL);
			break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

void InitDialogBox1 (HWND hWnd)
{
	DlgInitProgress1.controls=CtrlInitProgress1;
	DialogBoxIndirectParam (&DlgInitProgress1, hWnd, InitDialogBoxProc1, 0L);
}


#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif


