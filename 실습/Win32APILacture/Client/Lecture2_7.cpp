#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class name";
LPCTSTR lpszWindowName = L"Window Programming 2-6";
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
		0, 0, 800, 700, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static SIZE size;
	static TCHAR str[10][80];

	static int xcount;
	static int ycount;
	static int i;
	static int c;
	static int mod;


	switch (iMsg) {
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15);
		ShowCaret(hwnd);
		xcount = 0;
		ycount = 0;
		c = 0;
		mod = 0;

		break;

	case WM_CHAR:
		if (wParam == VK_RETURN) {
			if (ycount < 9) {
				xcount = 0;
				++ycount;
			}
			else if (ycount = 9) {
				xcount = 0;
				ycount = 0;
				c = 1;
			}
		}
		else if (wParam == VK_BACK) {
			xcount--;
		}
		else if (wParam == VK_TAB) {
			int i = 0;
			for (int i = 0; i < 80; ++i) {
				if (str[ycount][xcount] != ' ') {
					--xcount;
				}
				else if (str[xcount][ycount] == ' ') {
					i = 80;
				}
			}
		}
		else if (wParam == VK_ESCAPE) {
			xcount = 0;
			ycount = 0;

			InvalidateRect(hwnd, NULL, TRUE);
		}
		/*else if (wParam == VK_TAB) {
			for (int i = 0; i < 4; ++i) {
				str[ycount][xcount] = ' ';
				xcount++;
			}
		}*/
		/*else if (wParam == VK_TAB) {
			if (mod == 0) {
				mod = 1;
			}
			else if (mod == 1) {
				mod = 0;
			}
		}*/
		else {
			if (mod == 0) {
				if (xcount < 79) {
					str[ycount][xcount++] = wParam;
				}
				else if (xcount = 79) {
					xcount = 0;
					++ycount;
				}
			}
			else if (mod == 1) {
				if (xcount < 79) {
					--xcount;
					str[ycount][xcount++] = wParam;
					mod = 0;
				}
				else if (xcount = 79) {
					xcount = 0;
					++ycount;
				}
			}
		}
		str[ycount][xcount] = '\0';

		if (c == 0) {
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (c == 1) {
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < ycount + 1; ++i) {
			GetTextExtentPoint32(hdc, str[i], lstrlen(str[i]), &size); //--- 문자열 길이 알아내기
			TextOut(hdc, 0, i * 15, str[i], _tcslen(str[i]));
			//--- 캐럿 위치하기		
		}
		SetCaretPos(size.cx, (i - 1) * 15);

		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if ((xcount >= 80) && (ycount < 9)) {
			xcount = 0;
			ycount++;
		}
		else if ((xcount >= 80) && (ycount = 9)) {
			xcount = 0;
			ycount = 0;
			c = 1;
		}
		break;

	case WM_DESTROY:
		HideCaret(hwnd); //--- 캐럿 숨기기
		DestroyCaret(); //--- 캐럿 삭제하기
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}