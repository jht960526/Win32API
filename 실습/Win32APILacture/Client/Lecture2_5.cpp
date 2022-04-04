#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-2";
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
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// Variable
	srand(time(NULL));

	static SIZE size;
	static TCHAR str[30][10];
	static int colCount;
	static int rowCount;
	// Struct
	PAINTSTRUCT ps;
	HDC Hdc;
	

	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL,5,15);
		ShowCaret(hWnd);
		colCount = 0;
		rowCount = 0;
		break;

	case WM_CHAR:
		// 문자 저장 후 인덱스 증가
		str[colCount++][rowCount] = wParam;

		// 문자열은 null로 끝
		str[colCount][rowCount] = '\0';

		if(colCount < 9)
		{
			colCount = 0;
			rowCount++;
		}

		if(rowCount != 10)
		{
			if(colCount >= 0 && colCount <= 30)
			{
				str[rowCount][colCount] = '\0';
				rowCount++;
				colCount = 0;
			}
			else
			{
				str[rowCount][colCount++] = wParam;
			}

			if(colCount == 30)
			{
				str[rowCount][colCount] = '\0';
				rowCount++;
				colCount = 0;
			}
		}
		
		InvalidateRect(hWnd,NULL,true);
		break;

	case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);

		for(int i = 0; i < rowCount; ++i)
		{
			TextOut(Hdc,0, i * 15, str[i], _tcslen(str[i]));
		}
		GetTextExtentPoint(Hdc, str[rowCount],_tcslen(str[rowCount]),&size);
		SetCaretPos(size.cx,rowCount * 15);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}