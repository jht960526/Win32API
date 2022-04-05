#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-5";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	int row = 800;
	int col = 600;

	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, row, col, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// Variable
	static SIZE size;
	static TCHAR str[10][30];
	static int count, yPos;
	static int i;

	// Struct
	PAINTSTRUCT ps;
	HDC Hdc;
	

	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL,5,15);
		ShowCaret(hWnd);
		count = 0;
		yPos = 0;
		break;

	case WM_CHAR:

		if(yPos != 10)
		{
			if(wParam == VK_RETURN && count >= 0 && count <= 29)
			{
				str[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
			else if(wParam == VK_BACK)
			{
				if(count > 0)
				{
					count--;
					str[yPos][count] = NULL;
				}
				else if(count == 0)
				{
					yPos--;
					count = _tcslen(str[yPos]);
					count--;
					str[yPos][count] = NULL;
				}
			}

			else
			{
				str[yPos][count++] = wParam;
				str[yPos][count] = '\0';
			}

			if (count == 29)
			{
				str[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
			
		}
		

		InvalidateRect(hWnd,NULL,true);
		break;

	case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);

		for(i = 0; i <= yPos; ++i)
		{
			TextOut(Hdc, 0, i * 15, str[i], _tcslen(str[i]));
		}
		GetTextExtentPoint(Hdc, str[yPos], _tcslen(str[yPos]), &size);
		SetCaretPos(size.cx, yPos * 15);

		EndPaint(hWnd, &ps);
		break;

	
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyCaret();
		HideCaret(hWnd);
		DestroyCaret();
		
		break;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}