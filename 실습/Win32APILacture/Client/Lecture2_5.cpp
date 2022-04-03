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

	// Struct
	PAINTSTRUCT ps;
	HDC Hdc;
	TCHAR temp[100];
	TCHAR RectStr[56] = _T("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzab");
	TCHAR RectStr2[56] = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOP");

	// Rect
	RECT rect1{ 0, 0, 100, 75 };
	RECT rect2{ 0,75,100,150 };
	RECT rect3{ 100,0,200,75 };
	RECT rect4{ 100,75,200,150 };


	switch (iMessage)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);


		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		DrawText(Hdc, RectStr, _tcslen(RectStr), &rect1, DT_WORDBREAK | DT_EDITCONTROL);
		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		DrawText(Hdc, RectStr2, _tcslen(RectStr), &rect2, DT_WORDBREAK | DT_EDITCONTROL);
		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		DrawText(Hdc, RectStr2, _tcslen(RectStr), &rect3, DT_WORDBREAK | DT_EDITCONTROL);
		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		DrawText(Hdc, RectStr, _tcslen(RectStr), &rect4, DT_WORDBREAK | DT_EDITCONTROL);
		SetTextColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(Hdc, RGB(rand() % 256, rand() % 256, rand() % 256));

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}