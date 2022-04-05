#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class name";
LPCTSTR lpszWindowName = L"Window Programming 2-7";
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
		0, 0, 1050, 850, NULL, (HMENU)NULL, hInstance, NULL);
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
	HPEN hPen, oldPen;
	HBRUSH hbr, oldBrush;

	srand(time(NULL));

	POINT point1[10] = { {750,300}, {850,370}, {817, 500}, {683, 500}, {650, 370} };

	POINT point2[10] = { {400,50}, {600,50}, {500, 150}, {400, 250}, {600, 250} };

	POINT point3[10] = { {250, 300}, {150, 500}, {350, 500} };

	POINT point4[10] = { {500, 300}, {400, 500}, {600, 500} }; // 사각형 내부 삼각형

	POINT point5[10] = { {500,300}, {600,370}, {567, 500}, {433, 500}, {400, 370} };

	POINT point6[10] = { {400,300}, {600,300}, {500, 400}, {400, 500}, {600, 500} };

	int br = 0;
	int bg = 0;
	int bb = 255;

	int rr = 255;
	int rg = 0;
	int rb = 0;

	int yr = 255;
	int yg = 255;
	int yb = 0;

	int gr = 0;
	int gg = 255;
	int gb = 0;

	switch (iMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); // DC 얻어오기

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
		oldBrush = (HBRUSH)SelectObject(hdc, hbr);
		Rectangle(hdc, 380, 280, 620, 520); // 선택한 펜으로 도형 그리기
		SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
		hbr = CreateSolidBrush(RGB(gr, gg, gb));
		oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
		oldBrush = (HBRUSH)SelectObject(hdc, hbr);

		Pie(hdc, 400, 550, 600, 750, 500, 550, 500, 650); // 선택한 펜으로 도형 그리기
		SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
		hbr = CreateSolidBrush(RGB(yr, yr, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
		oldBrush = (HBRUSH)SelectObject(hdc, hbr);

		Polygon(hdc, point1, 5);
		SelectObject(hdc, oldPen);

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
		hbr = CreateSolidBrush(RGB(rr, rg, rb));
		oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
		oldBrush = (HBRUSH)SelectObject(hdc, hbr);

		Polygon(hdc, point2, 5);
		SelectObject(hdc, oldPen);

		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
		hbr = CreateSolidBrush(RGB(br, bg, bb));
		oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
		oldBrush = (HBRUSH)SelectObject(hdc, hbr);

		Polygon(hdc, point3, 3);
		SelectObject(hdc, oldPen);

		DeleteObject(hPen); // 만든 펜 객체 삭제하기
		EndPaint(hwnd, &ps); // DC 해제하기

		break;
	case WM_KEYDOWN:
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		if (wParam == 0x54 || wParam == 0x74) {

			br = rand() % 255;
			bg = rand() % 255;
			bb = rand() % 255;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(br, bg, bb));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point3, 3);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		else if (wParam == 's' || wParam == 'S') {

			rr = rand() % 255;
			rg = rand() % 255;
			rb = rand() % 255;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(rr, rg, rb));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point2, 5);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기

		}
		else if (wParam == 'e' || wParam == 'E') {

			gr = rand() % 255;
			gg = rand() % 255;
			gb = rand() % 255;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(gr, gg, gb));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Pie(hdc, 400, 550, 600, 750, 500, 550, 500, 650); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
			DeleteObject(hPen); // 만든 펜 객체 삭제하기

		}
		else if (wParam == 'p' || wParam == 'P') {

			yr = rand() % 255;
			yg = rand() % 255;
			yb = rand() % 255;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(yr, yg, yb));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point1, 5);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		else if (wParam == VK_LEFT) {
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = (HBRUSH)GetStockObject(RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);
			Rectangle(hdc, 380, 280, 620, 520); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(rand() % 255 + 50, rand() % 255, rand() % 255));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point4, 3);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		else if (wParam == VK_RIGHT) {
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = (HBRUSH)GetStockObject(RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);
			Rectangle(hdc, 380, 280, 620, 520); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(rand() % 122, rand() % 255, rand() % 5));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point5, 5);
			SelectObject(hdc, oldPen);
		}
		else if (wParam == VK_UP) {
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = (HBRUSH)GetStockObject(RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);
			Rectangle(hdc, 380, 280, 620, 520); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(rand() % 100, rand() % 5, rand() % 255));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point6, 5);
			SelectObject(hdc, oldPen);
		}
		else if (wParam == VK_DOWN) {
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = (HBRUSH)GetStockObject(RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);
			Rectangle(hdc, 380, 280, 620, 520); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Pie(hdc, 400, 300, 600, 500, 500, 300, 600, 400); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		EndPaint(hwnd, &ps); // DC 해제하기
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		if (wParam == 0x54 || wParam == 0x74) {
			br = 0;
			bg = 0;
			bb = 255;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(br, bg, bb));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point3, 3);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		else if (wParam == 's' || wParam == 'S') {

			rr = 255;
			rg = 0;
			rb = 0;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point2, 5);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기

		}
		else if (wParam == 'e' || wParam == 'E') {

			gr = 0;
			gg = 255;
			gb = 0;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(0, 255, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Pie(hdc, 400, 550, 600, 750, 500, 550, 500, 650); // 선택한 펜으로 도형 그리기
			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
			DeleteObject(hPen); // 만든 펜 객체 삭제하기

		}
		else if (wParam == 'p' || wParam == 'P') {

			yr = 255;
			yg = 255;
			yb = 0;

			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
			hbr = CreateSolidBrush(RGB(255, 255, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
			oldBrush = (HBRUSH)SelectObject(hdc, hbr);

			Polygon(hdc, point1, 5);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen); // 만든 펜 객체 삭제하기
		}
		EndPaint(hwnd, &ps); // DC 해제하기
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}