#include "client.h"
#include "qq_ui.h"


static DLGTEMPLATE DlgInitProgress=
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	100,150,300,120,
	"Loading...",
	0,0,
	3,NULL,
	0
};


static CTRLDATA CtrlInitProgress[]=
{
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_SIMPLE ,
		10,10,280,100,
		IDC_STATIC,
		"Please wait a few secs ...",
		0
	},
	{
		CTRL_PROGRESSBAR,
		WS_VISIBLE | WS_CHILD | PBS_NOTIFY,
		10,40,280,20,
		IDC_PROGRESS,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_VISIBLE | WS_VISIBLE | BS_DEFPUSHBUTTON,
		130,70,50,20,
		IDCANCEL,
		"Abort",
		0
	}
};


static int InitProgressBarProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
		//SendDlgItemMessage(hDlg,IDC_PROGRESS,PBM_SETPOS,20,0L);
	switch(message)
	{
		case MSG_INITDIALOG:
			progressbar_hwnd=hDlg;
			return 1;

		case MSG_COMMAND:
			switch(wParam)
			{
				case IDOK:
				
		SendDlgItemMessage(hDlg,IDC_PROGRESS,PBM_STEPIT,20,0L);
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

void InitProgressBar (HWND hWnd)
{
	DlgInitProgress.controls=CtrlInitProgress;
	DialogBoxIndirectParam (&DlgInitProgress, hWnd, InitProgressBarProc, 0L);
}

#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif
