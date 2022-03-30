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
		0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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

	int x = rand() % 700;
	int y = rand() % 500;
	int n = rand() % 9;
	int count = rand() % 100;

	int red = rand() % 255;
	int blue = rand() % 255;
	int green = rand() % 255;

	// Struct
	PAINTSTRUCT ps;
	HDC Hdc;
	TCHAR temp[100];
	TCHAR RectStr[56] = _T("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzab");
	COLORREF Rect1Color(RGB(red,blue,green));

	// Rect
	RECT rect;
	RECT rect1{0, 0, 100, 75};
	RECT rect2;
	RECT rect3;
	RECT rect4;


	switch (iMessage)
	{
		case WM_CREATE:
		break;

		case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);
		wsprintf(temp, L"%d", n);
		//wsprintf(RectStr,L"%c");

		//rect1.left = 0;
		//rect1.top = 0;
		//rect1.right = 400;
		//rect1.bottom = 300;

		SetBkColor(Hdc, Rect1Color);

		for(int i = 0; i < 14; ++i)
		{
			
		}
		DrawText(Hdc, RectStr,  _tcslen(RectStr), &rect1, DT_WORDBREAK);
		
		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));


		//for(int i = 0; i < )

		//DrawText(hDC, temp, count, &rect, DT_SINGLELINE);
		for (int i = 0; i < count; ++i) {
			for (int q = 0; q < count; ++q) {
				TextOut(Hdc, x + (i*8), y + (q*13), temp, 1);
			}
		}

		EndPaint(hWnd, &ps);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;

	}
		return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
