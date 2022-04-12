#include <windows.h>
#include <tchar.h>

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-10";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	WndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = nullptr;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, nullptr, (HMENU)nullptr, hInstance, nullptr);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT __stdcall WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC Hdc;
	HPEN hPen, oldPen;
	static TCHAR str[100];
	static int count;
	static SIZE size;

	// RECT
	RECT rt = { 0,570,800,600 };

	// 메시지 처리하기
	switch (iMessage)
	{
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;

	case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));
		GetTextExtentPoint(Hdc, str, _tcslen(str), &size);
		TextOut(Hdc, 0, 0, str, _tcslen(str));
		SetCaretPos(size.cx, 0);
		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		if (wParam == VK_BACK && count > 0) count--;
		else str[count++] = wParam;
		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, true);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	// 이외의 메세지는 OS로
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
