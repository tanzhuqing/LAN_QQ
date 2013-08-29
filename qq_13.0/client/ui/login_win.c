/*#include <stdio.h> 
 
#include <minigui/common.h> 
#include <minigui/minigui.h> 
#include <minigui/gdi.h> 
#include <minigui/window.h> 
#include <minigui/control.h>
#include "client.h"

void InitDialogBox1 (HWND hWnd);
*/
#include "client.h"
#include "qq_ui.h"


static DLGTEMPLATE DlgInitProgress=
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	100,100,240,220,
	"LOGIN",
	0,0,
	7,NULL,
	0
};

#define IDC_CHAR1 100
#define IDC_CHAR2 101
#define IDREGSTER 201

static CTRLDATA CtrlInitProgress[]=
{/*
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE ,
		70,50,160,20,
		IDC_STATIC,
		" ",
		0
	},*/
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,40,60,20,
		IDC_STATIC,
		"ID",
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE,
		20,70,60,20,
		IDC_STATIC,
		"Passwd",
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER,
		90,40,100,20,
		IDC_CHAR1,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_TABSTOP | WS_VISIBLE | WS_BORDER |ES_PASSWORD,
		90,70,100,20,
		IDC_CHAR2,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		35,130,60,20,
		IDOK,
		"Confirm",
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		140,130,60,20,
		IDCANCEL,
		"Cancel",
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		160,10,60,20,
		IDREGSTER,
		"Register",
		0
	}
};

static int InitDialogBoxProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
//HWND hProhar;	
	switch(message)
	{
		case MSG_INITDIALOG:
			connect_server();
			return 1;

		case MSG_COMMAND:
			switch(wParam)
			{
				case IDOK:
				{
					//	InitProgressBar(hDlg);
					char buff_1 [40];
					char buff_2 [40];
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR1),buff_1,40);
					GetWindowText (GetDlgItem(hDlg,IDC_CHAR2),buff_2,40);
					if(checkPasswd(buff_1,buff_2)>0)
					{	//MessageBox (hDlg,"Login Success","^_^",MB_OK);
						EndDialog(hDlg, wParam);
				
						pthread_t t1 , t2 ;
						pthread_create(&t1, NULL, pthreadInitFriendlist, NULL);
						sleep(1);
						pthread_create(&t2, NULL, waitCombine, NULL);
					
					}	
					else
						MessageBox (hDlg,"Login Fail","- -|",MB_OK);

						break;
				}
				case IDREGSTER:
				
				//	EndDialog(hDlg, wParam);
					InitDialogBox1(HWND_DESKTOP);	
					break;
				case IDCANCEL:
					EndDialog(hDlg, wParam);
					break;
			}
			break;
		case MSG_CLOSE:
			EndDialog(hDlg, IDCANCEL);
			break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

void InitDialogBox (HWND hWnd)
{
	DlgInitProgress.controls=CtrlInitProgress;
	DialogBoxIndirectParam (&DlgInitProgress, hWnd, InitDialogBoxProc, 0L);
}

int MiniGUIMain (int argc, const char* argv[])
{
#ifdef _MGRM_PROCESSES
	JoinLayer (NAME_DEF_LAYER, "dialogbox", 0, 0);
#endif
	InitDialogBox (HWND_DESKTOP);
	return 0;
}

#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif


