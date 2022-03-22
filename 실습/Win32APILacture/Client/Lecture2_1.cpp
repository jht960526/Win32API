#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-1";
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 715, 690, NULL, (HMENU)NULL, hInstance, NULL);
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
	PAINTSTRUCT ps;
	HDC hDC;
	TCHAR LTtemp[] = TEXT(" Left-top (0, 0) ");
	TCHAR RTtemp[] = TEXT(" Right-top (700, 0) ");
	TCHAR Ctemp[] = TEXT(" Center (350, 300) ");
	TCHAR RBtemp[] = TEXT(" Right-bottom (700, 650) ");
	TCHAR LBtemp[] = TEXT(" Left-bottom (0, 650) ");
	RECT rect;

	switch (iMessage) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		rect.left = 0;
		rect.top = 0;
		rect.right = 680; 
		rect.bottom = 700; 

		SetTextColor(hDC, RGB(255, 0, 0));
		SetBkColor(hDC, RGB(100, 100, 0));
		DrawText(hDC, LTtemp, _tcslen(LTtemp), &rect, DT_TOP | DT_LEFT | DT_SINGLELINE);

		rect.left = 550;
		rect.top = 0;
		rect.right = 700;
		rect.bottom = 650;

		SetTextColor(hDC, RGB(155, 110, 100));
		SetBkColor(hDC, RGB(200, 10, 100));
		DrawText(hDC, RTtemp, _tcslen(RTtemp), &rect, DT_TOP | DT_RIGHT | DT_SINGLELINE);
	
		rect.left = 280;
		rect.top = 180;
		rect.right = 420;
		rect.bottom = 420;

		SetTextColor(hDC, RGB(0, 250, 0));
		SetBkColor(hDC, RGB(0, 50, 10));
		DrawText(hDC, Ctemp, _tcslen(Ctemp), &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

		rect.left = 500;
		rect.top = 500;
		rect.right = 700;
		rect.bottom = 650;

		SetTextColor(hDC, RGB(0, 0, 230));
		SetBkColor(hDC, RGB(0, 0, 80));
		DrawText(hDC, RBtemp, _tcslen(RBtemp), &rect, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);

		rect.left = 0;
		rect.top = 530;
		rect.right = 680;
		rect.bottom = 650;

		SetTextColor(hDC, RGB(200, 80, 10));
		SetBkColor(hDC, RGB(100, 100, 100));
		DrawText(hDC, LBtemp, _tcslen(LBtemp), &rect, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}