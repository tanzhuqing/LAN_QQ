#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDC_CHAR_READ 300
#define IDC_CHAR_WRITE 301
#define IDC_PROGRESS 999


HWND friend_list_hwnd;
HWND progressbar_hwnd;
void InitDialogBox (HWND hwnd);
void InitDialogBox1 (HWND hWnd);
void InitDialogBox2 (HWND hWnd);
void testDialogFriendlist (HWND hWnd);
void InitProgressBar (HWND hWnd);
void InitDialogBox3(HWND hWnd,HWND hDlg);



