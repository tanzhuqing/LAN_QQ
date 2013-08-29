#include"client.h"
#include"qq_ui.h"
#define IDC_CHAT       99
#define IDC_CHAR        100
#define IDC_CHARS       110
//#define IDC_CHAT        120

unsigned char  buff[4096];
COMBINE comb;
int friend_id;

static DLGTEMPLATE DlgBoxInputChar =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    390,0, 200, 430, 
    "CHAT RECORD",
    0, 0,
    1, NULL,
    0
};
static CTRLDATA CtrlInputChar [] =
{ 
    {
        CTRL_MLEDIT,
        WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER | ES_READONLY,
        15, 20, 160, 350,
        IDC_CHAT,
        NULL,
        0
    }
};

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
		get_info(friend_id,buff);
		printf("1buff%s:\n",buff);
		SetDlgItemText(hwnd,IDC_CHAT,buff);
}       



static int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    HWND hwnd;

    switch (message) 
	{
    	case MSG_INITDIALOG:
        	//hwnd = GetDlgItem (hDlg, IDC_CHAR);
        //	SetNotificationCallback (hwnd, my_notif_proc);
     	    get_info(friend_id,buff);

			printf("buff=%s\n",buff);
			
	    	SetDlgItemText(hDlg,IDC_CHAT,buff);
	     	//SendMessage (hwnd, MSG_KEYDOWN, SCANCODE_INSERT, 0L);
//       		break;
			return 1;
        
    	case MSG_CLOSE:
        	EndDialog (hDlg, IDCANCEL);
       		 break;
        
   		 case MSG_COMMAND:
       		 switch (wParam)
			{
        		case IDOK:
					
        		case IDCANCEL:
            		EndDialog (hDlg, wParam);
            	break;
        }
        	break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}




static int chatWinProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc1,hdc2;
	static HWND hStaticWnd1,hStaticWnd2;
	switch(message)
	{
		case MSG_INITDIALOG:
		{
			hdc1=BeginPaint(hWnd);
			
		 	TextOut(hdc1,100,10,"CHAT RECORD");
		    hStaticWnd2=CreateWindow(CTRL_TEXTEDIT,"",WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_READONLY|SS_RIGHT,IDC_STATIC,10,30,280,130,hWnd,0);
			hdc2 = BeginPaint(hStaticWnd2);
         	    get_info(friend_id,buff);
				
				printf("buff%s\n\n\n\n\n\n",buff);
				SetDlgItemText(hWnd,IDC_CHAT,buff);	
			break;
		}

	case MSG_CLOSE:
		{
			EndDialog(hWnd,IDCANCEL);
			break;
		}
		#if 0
	case MSG_COMMAND:
		switch(wParam)
		{
			case IDOK:
			case IDCANCEL:
		}
		#endif
		default:
		{
			break;
		}
	}
	return DefaultMainWinProc(hWnd,message,wParam,lParam);
}



void  InitDialogBox3(HWND hWnd,HWND hDlg)
{
	friend_id=getIDbyWin(hDlg);
    DlgBoxInputChar.controls = CtrlInputChar;
    DialogBoxIndirectParam (&DlgBoxInputChar, HWND_DESKTOP, InputCharDialogBoxProc, 0L);

	comb.third_struct.user_id=getCurrentUserID();

}


