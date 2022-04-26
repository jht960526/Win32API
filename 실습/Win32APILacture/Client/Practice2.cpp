#include <windows.h>
#include <math.h>

#define BSIZE 40

double LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE)
	{
		return TRUE;
	}
	else
		return FALSE;
}

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 2";

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 100, 50, 800, 600, nullptr, (HMENU)nullptr, hInstance, nullptr);
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

	static int x, y;
	static BOOL Selection;
	int mx, my;
	static int startX, startY, oldX, oldY;
	static BOOL Drag;
	int endX, endY;


	// 메시지 처리하기
	switch (iMessage)
	{
	case WM_CREATE:

		x = 50;
		y = 50;
		Selection = FALSE;
		
		// 실습3_7
		startX = oldX = 50;
		startY = oldY = 50;
		Drag = FALSE;

		break;

	case WM_PAINT:
		Hdc = BeginPaint(hWnd, &ps);
		Ellipse(Hdc, startX, startY, oldX, oldY);

		if(Selection)
		{
			Rectangle(Hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		}
		Ellipse(Hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		Drag = TRUE;

		if(InCircle(x,y,mx,my))
		{
			Selection = TRUE;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		Drag = FALSE;
		Selection = FALSE;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE:

		Hdc = GetDC(hWnd);

		if(Drag)
		{
			SetROP2(Hdc, R2_XORPEN);
			SelectObject(Hdc, (HPEN)GetStockObject(WHITE_PEN));
			SelectObject(Hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			Ellipse(Hdc, startX, startY, oldX, oldY);
			Ellipse(Hdc, startX, startY, endX, endY);
			
			oldX = endX;
			oldY = endY;
		}
		ReleaseDC(hWnd,Hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	// 이외의 메세지는 OS로
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}