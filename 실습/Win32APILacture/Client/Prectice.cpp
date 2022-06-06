#include <windows.h>
#include <tchar.h>
#include "resource2.h"

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 1";

LRESULT CALLBACK WndProc (HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlalog_Proc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hinst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(nullptr,IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(nullptr,IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = nullptr;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(nullptr,IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, nullptr, (HMENU)nullptr, hInstance, nullptr);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT __stdcall WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC Hdc,memdc, mem1dc, mem2dc;
	static HBITMAP hBit1, hBit2;
	HBITMAP oldBit1, oldBit2;
	static HBITMAP hBitmap,oldBit;
	TCHAR word[] = L"더블 버퍼링 실습";
	static int yPos;

	// 메시지 처리하기
	switch (iMessage)
	{
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadBitmap(g_hinst,MAKEINTRESOURCE(IDB_BITMAP1));

		yPos = -30;

		break;

	case WM_PAINT:
        Hdc = BeginPaint(hWnd,&ps);

		memdc = CreateCompatibleDC(Hdc);
		SelectObject(memdc,hBitmap);
		StretchBlt(Hdc,100,0,160,120,memdc,0,0,320,240,SRCCOPY);
		
		DeleteDC(memdc);
        EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1),hWnd,Dlalog_Proc);
		break;

    case WM_KEYDOWN:
        
        switch (wParam)
        {

        case 's':
            SetTimer(hWnd, 1, 100, NULL);
            break;

        case 'S':
            SetTimer(hWnd, 1, 100, NULL);
            break;

        case 'Q':
            PostQuitMessage(0);
            return 0;

        case 'q':
            PostQuitMessage(0);
            return 0;
        }

        break;

    case WM_TIMER:

       
        InvalidateRect(hWnd, NULL, TRUE);
        break;


	case WM_DESTROY:
		DeleteObject(hBitmap);
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
		break;
	}

	// 이외의 메세지는 OS로
	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}

BOOL __stdcall Dlalog_Proc(HWND hDIg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			hdc = GetDC(hDIg);
			TextOut(hdc,0,0,L"Hello World", 11);
			ReleaseDC(hDIg,hdc);
			break;

		case IDC_BUTTON2:
			MessageBox(hDIg, L"Stop Button", L"test", MB_OK);
			break;

		case IDCANCEL:
			EndDialog(hDIg,0);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hDIg, 0);
		break;
	}
	return 0;
}