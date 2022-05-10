#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <math.h>
#include "resource.h"

int colormode = 0;
int sizemode = 0;
int cutmode = 1;

int twocutmode = 0;
int threecutmode = 0;

struct image {
	int startx;
	int starty;
	int endx;
	int endy;
};

image one = { 0, 0, 500, 500 };

image two[4] = {
	{0, 0, 500, 500},
	{500, 0, 500, 500},
	{0, 500, 500, 500},
	{500, 500, 500, 500}
};

image three[9] = {
	{0, 0, 333, 333}, //(0,0)
	{333, 0, 333, 333}, //(1,0)
	{666, 0, 333, 333}, //(2,0)
	{0, 333, 333, 333}, //(0,1)
	{333, 333, 333, 333}, //(1,1)
	{666, 333, 333, 333}, //(2,1)
	{0, 666, 333, 333}, //(0,2)
	{333, 666, 333, 333}, //(1,2)
	{666, 666, 333, 333}, //(2,2)
};

BOOL InRec(int x, int y, int x2, int y2, int ckx, int cky)
{
	if (ckx > x && ckx < x2 && cky > y && cky < y2)
		return TRUE;
	else
		return FALSE;
}

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 5-1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	// 윈도우 클래스 구조체 값 설정
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

	hWnd = CreateWindow(
		lpszClass, lpszWindowName, WS_SYSMENU, 0, 0, 1000, 1000, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;
	static int mx, my;
	HPEN hPen, oldPen;
	HBRUSH hbr, oldBrush;
	RECT rect;

	switch (uMsg) {
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hBitmap);
		if (cutmode == 1) {
			if (colormode == 0) {
				if (sizemode == 0) {
					BitBlt(hdc, one.startx, one.starty, one.endx, one.endy, memdc, 0, 0, SRCCOPY); //--- memdc 에 있는 그림에서 (0, 0) 위치에 (500, 500) 크기로 그리기
					//--- SRCCOPY : 바탕색과 관계없이 소스값을 그대로 그리기
				}
				else if (sizemode == 1) {
					StretchBlt(hdc, 0, 0, 1000, 1000, memdc, one.startx, one.starty, one.endx, one.endy, SRCCOPY);//StretchBlt(hdc, 0, 0, 800, 800, memdc, 0, 0, 100, 100, SRCCOPY);
				//--- 메모리 DC에 있는 그림에서 (0, 0)위치에서 (320, 240) 크기의 그림을
				//--- 화면의 (100, 0)위치에 (160, 120) 크기로 이미지 색 그대로 그리기
				}
			}
			else if (colormode == 1) {
				if (sizemode == 0) {
					BitBlt(hdc, one.startx, one.starty, one.endx, one.endy, memdc, 0, 0, NOTSRCCOPY);
					//--- NOTSRCCOPY : 색상반전
				}
				else if (sizemode == 1) {
					StretchBlt(hdc, 0, 0, 1000, 1000, memdc, one.startx, one.starty, one.endx, one.endy, NOTSRCCOPY);
				}
			}
		}
		else if (cutmode == 2) {
			if (colormode == 0) {
				BitBlt(hdc, two[0].startx, two[0].starty, two[0].endx, two[0].endy, memdc, 0, 0, SRCCOPY);
				BitBlt(hdc, two[1].startx, two[1].starty, two[1].endx, two[1].endy, memdc, 0, 0, NOTSRCCOPY);
				BitBlt(hdc, two[2].startx, two[2].starty, two[2].endx, two[2].endy, memdc, 0, 0, NOTSRCCOPY);
				BitBlt(hdc, two[3].startx, two[3].starty, two[3].endx, two[3].endy, memdc, 0, 0, SRCCOPY);
			}
			else if (colormode == 1) {
				BitBlt(hdc, two[0].startx, two[0].starty, two[0].endx, two[0].endy, memdc, 0, 0, NOTSRCCOPY);
				BitBlt(hdc, two[1].startx, two[1].starty, two[1].endx, two[1].endy, memdc, 0, 0, SRCCOPY);
				BitBlt(hdc, two[2].startx, two[2].starty, two[2].endx, two[2].endy, memdc, 0, 0, SRCCOPY);
				BitBlt(hdc, two[3].startx, two[3].starty, two[3].endx, two[3].endy, memdc, 0, 0, NOTSRCCOPY);
			}
		}
		else if (cutmode == 3) {
			if (colormode == 0) {
				StretchBlt(hdc, three[0].startx, three[0].starty, three[0].endx, three[0].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[1].startx, three[1].starty, three[1].endx, three[1].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[2].startx, three[2].starty, three[2].endx, three[2].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[3].startx, three[3].starty, three[3].endx, three[3].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[4].startx, three[4].starty, three[4].endx, three[4].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[5].startx, three[5].starty, three[5].endx, three[5].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[6].startx, three[6].starty, three[6].endx, three[6].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[7].startx, three[7].starty, three[7].endx, three[7].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[8].startx, three[8].starty, three[8].endx, three[8].endy, memdc, 0, 0, 500, 500, SRCCOPY);
			}
			else if (colormode == 1) {
				StretchBlt(hdc, three[0].startx, three[0].starty, three[0].endx, three[0].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[1].startx, three[1].starty, three[1].endx, three[1].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[2].startx, three[2].starty, three[2].endx, three[2].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[3].startx, three[3].starty, three[3].endx, three[3].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[4].startx, three[4].starty, three[4].endx, three[4].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[5].startx, three[5].starty, three[5].endx, three[5].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[6].startx, three[6].starty, three[6].endx, three[6].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
				StretchBlt(hdc, three[7].startx, three[7].starty, three[7].endx, three[7].endy, memdc, 0, 0, 500, 500, SRCCOPY);
				StretchBlt(hdc, three[8].startx, three[8].starty, three[8].endx, three[8].endy, memdc, 0, 0, 500, 500, NOTSRCCOPY);
			}
		}

		if (cutmode == 2) {
			if (twocutmode == 1) {
				rect = { two[0].startx , two[0].starty , two[0].startx + 500, two[0].starty + 500 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (twocutmode == 2) {
				rect = { two[1].startx , two[1].starty , two[1].startx + 500, two[1].starty + 500 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			if (twocutmode == 3) {
				rect = { two[2].startx , two[2].starty , two[2].startx + 500, two[2].starty + 500 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			if (twocutmode == 4) {
				rect = { two[3].startx , two[3].starty , two[3].startx + 500, two[3].starty + 500 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
		}
		else if (cutmode == 3) {
			if (threecutmode == 1) {
				rect = { three[0].startx , three[0].starty , three[0].startx + 333, three[0].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 2) {
				rect = { three[1].startx , three[1].starty , three[1].startx + 333, three[1].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 3) {
				rect = { three[2].startx , three[2].starty , three[2].startx + 333, three[2].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 4) {
				rect = { three[3].startx , three[3].starty , three[3].startx + 333, three[3].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 5) {
				rect = { three[4].startx , three[4].starty , three[4].startx + 333, three[4].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 6) {
				rect = { three[5].startx , three[5].starty , three[5].startx + 333, three[5].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 7) {
				rect = { three[6].startx , three[6].starty , three[6].startx + 333, three[6].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 8) {
				rect = { three[7].startx , three[7].starty , three[7].startx + 333, three[7].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
			else if (threecutmode == 9) {
				rect = { three[8].startx , three[8].starty , three[8].startx + 333, three[8].starty + 333 };
				FrameRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
			}
		}

		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == 'r' || wParam == 'R') {
			if (colormode == 0) {
				colormode = 1;
			}
			else if (colormode == 1) {
				colormode = 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (wParam == 'a' || wParam == 'A') {
			if (sizemode == 0) {
				sizemode = 1;
			}
			else if (sizemode == 1) {
				sizemode = 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
		}
		else if (wParam == '1') {
			if (cutmode == 2 || cutmode == 3) {
				cutmode = 1;
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		else if (wParam == '2') {
			if (cutmode == 1 || cutmode == 3) {
				cutmode = 2;
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		else if (wParam == '3') {
			if (cutmode == 1 || cutmode == 2) {
				cutmode = 3;
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		else if (wParam == VK_LEFT) {
			if (cutmode == 1) {
				one.startx--;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (cutmode == 2) {
				if (twocutmode == 1) {
					two[0].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 2) {
					two[1].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 3) {
					two[2].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 4) {
					two[3].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
			else if (cutmode == 3) {
				if (threecutmode == 1) {
					three[0].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 2) {
					three[1].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 3) {
					three[2].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 4) {
					three[3].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 5) {
					three[4].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 6) {
					three[5].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 7) {
					three[6].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 8) {
					three[7].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 9) {
					three[8].startx--;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
		else if (wParam == VK_RIGHT) {
			if (cutmode == 1) {
				one.startx++;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (cutmode == 2) {
				if (twocutmode == 1) {
					two[0].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 2) {
					two[1].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 3) {
					two[2].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (twocutmode == 4) {
					two[3].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
			else if (cutmode == 3) {
				if (threecutmode == 1) {
					three[0].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 2) {
					three[1].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 3) {
					three[2].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 4) {
					three[3].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 5) {
					three[4].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 6) {
					three[5].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 7) {
					three[6].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 8) {
					three[7].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else if (threecutmode == 9) {
					three[8].startx++;
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
		break;
	case WM_LBUTTONDOWN: //--- 왼쪽 버튼 누르면
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (cutmode == 2) {
			if (InRec(two[0].startx, two[0].starty, two[0].endx, two[0].endy, mx, my)) {
				twocutmode = 1;
			}
			else if (InRec(two[1].startx, two[1].starty, two[1].startx + 500, two[1].starty + 500, mx, my)) {
				twocutmode = 2;
			}
			else if (InRec(two[2].startx, two[2].starty, two[2].startx + 500, two[2].starty + 500, mx, my)) {
				twocutmode = 3;
			}
			else if (InRec(two[3].startx, two[3].starty, two[3].startx + 500, two[3].starty + 500, mx, my)) {
				twocutmode = 4;
			}
		}
		else if (cutmode == 3) {
			if (InRec(three[0].startx, three[0].starty, three[0].startx + 333, three[0].starty + 333, mx, my)) {
				threecutmode = 1;
			}
			else if (InRec(three[1].startx, three[1].starty, three[1].startx + 333, three[1].starty + 333, mx, my)) {
				threecutmode = 2;
			}
			else if (InRec(three[2].startx, three[2].starty, three[2].startx + 333, three[2].starty + 333, mx, my)) {
				threecutmode = 3;
			}
			else if (InRec(three[3].startx, three[3].starty, three[3].startx + 333, three[3].starty + 333, mx, my)) {
				threecutmode = 4;
			}
			else if (InRec(three[4].startx, three[4].starty, three[4].startx + 333, three[4].starty + 333, mx, my)) {
				threecutmode = 5;
			}
			else if (InRec(three[5].startx, three[5].starty, three[5].startx + 333, three[5].starty + 333, mx, my)) {
				threecutmode = 6;
			}
			else if (InRec(three[6].startx, three[6].starty, three[6].startx + 333, three[6].starty + 333, mx, my)) {
				threecutmode = 7;
			}
			else if (InRec(three[7].startx, three[7].starty, three[7].startx + 333, three[7].starty + 333, mx, my)) {
				threecutmode = 8;
			}
			else if (InRec(three[8].startx, three[8].starty, three[8].startx + 333, three[8].starty + 333, mx, my)) {
				threecutmode = 9;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
