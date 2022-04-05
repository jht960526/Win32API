#include <Windows.h>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2-10";

typedef struct Shape {
	int x{};	// x좌표
	int y{};	// y좌표
	int r{};	// 색 r
	int g{};	// 색 g
	int b{};	// 색 b
	int type{}; // 도형 타입 1 : 원 2 : 삼각형 3 : 사각형 0 : 도형 없음
	BOOL check{}; // 도형 선택 체크 false : X, true : O
};

int mod = 0;

int cr, cg, cb, rr, rg, rb, sr, sg, sb;

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
		lpszClass, lpszWindowName, WS_SYSMENU, 0, 0, 617, 640, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	static TCHAR wP{};
	static int size{};			// 0 30 X 30, 1 40 X 40, 2 50 X 50
	static Shape shape[10];
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static POINT length;
	static RECT rt;
	static POINT point[4]{};
	static int cnt{};
	switch (uMsg) {
	case WM_CREATE:
		srand((unsigned int)time(NULL));
		GetClientRect(hWnd, &rt);
		for (int i = 0; i < 9; ++i) {
			shape[i].type = 0;
			shape[i].x = 0;
			shape[i].y = 0;
			shape[i].r = 0;
			shape[i].g = 0;
			shape[i].b = 0;
			shape[i].check = false;
		}
		length.x = rt.right / 50;
		length.y = rt.bottom / 50;
		size = 1;
		cnt = 0;
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP:
			for (int i = 0; i < 5; ++i) {
				if (shape[i].check == true) {
					shape[i].y--;
					if (shape[i].y < 0) {
						if (size == 0) {
							shape[i].y = 29;
						}
						else if (size == 1) {
							shape[i].y = 39;
						}
						else if (size == 2) {
							shape[i].y = 49;
						}
					}
				}
			}
			break;
		case VK_DOWN:
			for (int i = 0; i < 5; ++i) {
				if (shape[i].check == true) {
					shape[i].y++;
					if (size == 0 && shape[i].y > 29) {
						shape[i].y = 0;
					}
					else if (size == 1 && shape[i].y > 39) {
						shape[i].y = 0;
					}
					else if (size == 2 && shape[i].y > 49) {
						shape[i].y = 0;
					}
				}
			}
			break;
		case VK_LEFT:
			for (int i = 0; i < 5; ++i) {
				if (shape[i].check == true) {
					shape[i].x--;
					if (shape[i].x < 0) {
						if (size == 0) {
							shape[i].x = 29;
						}
						else if (size == 1) {
							shape[i].x = 39;
						}
						else if (size == 2) {
							shape[i].x = 49;
						}
					}
				}
			}
			break;
		case VK_RIGHT:
			for (int i = 0; i < 5; ++i) {
				if (shape[i].check == true) {
					shape[i].x++;
					if (size == 0 && shape[i].x > 29) {
						shape[i].x = 0;
					}
					else if (size == 1 && shape[i].x > 39) {
						shape[i].x = 0;
					}
					else if (size == 2 && shape[i].x > 49) {
						shape[i].x = 0;
					}
				}
			}
			break;
		case VK_DELETE:
			if (cnt == 9) {
				for (int i = 0; i < 9; ++i) {
					if (shape[i].check == true) {
						for (int j = i; j < 9; ++j) {
							shape[i].type = shape[i + 1].type;
							shape[i].x = shape[i + 1].x;
							shape[i].y = shape[i + 1].y;
							shape[i].r = shape[i + 1].r;
							shape[i].g = shape[i + 1].g;
							shape[i].b = shape[i + 1].b;
						}
						shape[i].check = false;
					}
				}
				cnt = 9;
			}
			else {
				for (int i = 0; i < 9; ++i) {
					if (shape[i].check == true) {
						for (int j = i; j < 9; ++j) {
							shape[i].type = shape[i + 1].type;
							shape[i].x = shape[i + 1].x;
							shape[i].y = shape[i + 1].y;
							shape[i].r = shape[i + 1].r;
							shape[i].g = shape[i + 1].g;
							shape[i].b = shape[i + 1].b;
						}
						shape[i].check = false;
					}
				}
				--cnt;
			}
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;

	case WM_CHAR:
		wP = wParam;
		switch (wP) {
		case '1':
			shape[0].check = true;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '2':
			shape[1].check = true;
			shape[0].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '3':
			shape[2].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '4':
			shape[3].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '5':
			shape[4].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '6':
			shape[5].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '7':
			shape[6].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[7].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '8':
			shape[7].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[8].check = false;
			shape[9].check = false;
			break;
		case '9':
			shape[8].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[9].check = false;
			break;
		case '0':
			shape[9].check = true;
			shape[0].check = false;
			shape[1].check = false;
			shape[2].check = false;
			shape[3].check = false;
			shape[4].check = false;
			shape[5].check = false;
			shape[6].check = false;
			shape[7].check = false;
			shape[8].check = false;
			break;
		case 's':
			size = 0;
			break;
		case 'm':
			size = 1;
			break;
		case 'l':
			size = 2;
			break;
		case 'e':				// 원
			if (cnt <= 9) {
				shape[cnt].type = 1;
				shape[cnt].r = rand() % 256;
				shape[cnt].g = rand() % 256;
				shape[cnt].b = rand() % 256;
				if (size == 0) {
					shape[cnt].x = rand() % 30;
					shape[cnt].y = rand() % 30;
				}
				else if (size == 1) {
					shape[cnt].x = rand() % 40;
					shape[cnt].y = rand() % 40;
				}
				else if (size == 2) {
					shape[cnt].x = rand() % 50;
					shape[cnt].y = rand() % 50;
				}
				++cnt;
				shape[cnt].check = false;
			}
			else {
				for (int i = 0; i < 9; i++)
				{
					shape[i].type = shape[i + 1].type;
					shape[i].x = shape[i + 1].x;
					shape[i].y = shape[i + 1].y;
					shape[i].r = shape[i + 1].r;
					shape[i].g = shape[i + 1].g;
					shape[i].b = shape[i + 1].b;
					shape[i].check = false;
				}
				shape[9].type = 1;
				shape[9].r = rand() % 256;
				shape[9].g = rand() % 256;
				shape[9].b = rand() % 256;

				if (size == 0) {
					shape[9].x = rand() % 30;
					shape[9].y = rand() % 30;
				}
				else if (size == 1) {
					shape[9].x = rand() % 40;
					shape[9].y = rand() % 40;
				}
				else if (size == 2) {
					shape[9].x = rand() % 50;
					shape[9].y = rand() % 50;
				}
			}
			break;
		case 't':				// 삼각형
			if (cnt <= 9) {
				shape[cnt].type = 2;
				shape[cnt].r = rand() % 256;
				shape[cnt].g = rand() % 256;
				shape[cnt].b = rand() % 256;
				if (size == 0) {
					shape[cnt].x = rand() % 30;
					shape[cnt].y = rand() % 30;
				}
				else if (size == 1) {
					shape[cnt].x = rand() % 40;
					shape[cnt].y = rand() % 40;
				}
				else if (size == 2) {
					shape[cnt].x = rand() % 50;
					shape[cnt].y = rand() % 50;
				}
				++cnt;
				shape[cnt].check = false;
			}
			else {
				for (int i = 0; i < 4; i++)
				{
					shape[i].type = shape[i + 1].type;
					shape[i].x = shape[i + 1].x;
					shape[i].y = shape[i + 1].y;
					shape[i].r = shape[i + 1].r;
					shape[i].g = shape[i + 1].g;
					shape[i].b = shape[i + 1].b;
					shape[i].check = false;
				}
				shape[9].type = 2;
				shape[9].r = rand() % 256;
				shape[9].g = rand() % 256;
				shape[9].b = rand() % 256;
				if (size == 0) {
					shape[9].x = rand() % 30;
					shape[9].y = rand() % 30;
				}
				else if (size == 1) {
					shape[9].x = rand() % 40;
					shape[9].y = rand() % 40;
				}
				else if (size == 2) {
					shape[9].x = rand() % 50;
					shape[9].y = rand() % 50;
				}
			}
			break;
		case 'r':				// 사각형
			if (cnt <= 9) {
				shape[cnt].type = 3;
				shape[cnt].r = rand() % 256;
				shape[cnt].g = rand() % 256;
				shape[cnt].b = rand() % 256;
				if (size == 0) {
					shape[cnt].x = rand() % 30;
					shape[cnt].y = rand() % 30;
				}
				else if (size == 1) {
					shape[cnt].x = rand() % 40;
					shape[cnt].y = rand() % 40;
				}
				else if (size == 2) {
					shape[cnt].x = rand() % 50;
					shape[cnt].y = rand() % 50;
				}
				++cnt;
				shape[cnt].check = false;
			}
			else {
				for (int i = 0; i < 4; i++)
				{
					shape[i].type = shape[i + 1].type;
					shape[i].x = shape[i + 1].x;
					shape[i].y = shape[i + 1].y;
					shape[i].r = shape[i + 1].r;
					shape[i].g = shape[i + 1].g;
					shape[i].b = shape[i + 1].b;
					shape[i].check = false;
				}
				shape[9].type = 3;
				shape[9].r = rand() % 256;
				shape[9].g = rand() % 256;
				shape[9].b = rand() % 256;
				if (size == 0) {
					shape[9].x = rand() % 30;
					shape[9].y = rand() % 30;
				}
				else if (size == 1) {
					shape[9].x = rand() % 40;
					shape[9].y = rand() % 40;
				}
				else if (size == 2) {
					shape[9].x = rand() % 50;
					shape[9].y = rand() % 50;
				}
			}
			break;
		case 'p':
			for (int i = 0; i < 9; ++i) {
				shape[i].type = 0;
			}
			cnt = 0;
			break;
		case 'c':
			if (mod == false) {
				mod = true;
				cr = rand() % 255;
				cg = rand() % 255;
				cb = rand() % 255;
				rr = rand() % 255;
				rg = rand() % 255;
				rb = rand() % 255;
				sr = rand() % 255;
				sg = rand() % 255;
				sb = rand() % 255;
			}
			else if (mod == true) {
				mod = false;
			}
			break;
		case 'q':
			PostQuitMessage(0);
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (size == 0) {
			for (int i = 0; i < 30; ++i) {
				for (int j = 0; j < 30; ++j) {
					Rectangle(hDC, i * length.x, j * length.y, (i + 1) * length.x, (j + 1) * length.y);
				}
			}
		}
		else if (size == 1) {
			for (int i = 0; i < 40; ++i) {
				for (int j = 0; j < 40; ++j) {
					Rectangle(hDC, i * length.x, j * length.y, (i + 1) * length.x, (j + 1) * length.y);
				}
			}
		}
		else if (size == 2) {
			for (int i = 0; i < 50; ++i) {
				for (int j = 0; j < 50; ++j) {
					Rectangle(hDC, i * length.x, j * length.y, (i + 1) * length.x, (j + 1) * length.y);
				}
			}
		}
		for (int i = 0; i < 10; ++i) {
			if (size == 0 && shape[i].x >= 30) {
				shape[i].x = 29;
			}
			else if (size == 0 && shape[i].y >= 30) {
				shape[i].y = 29;

			}
			if (size == 1 && shape[i].x >= 40) {
				shape[i].x = 39;
			}
			else if (size == 1 && shape[i].y >= 40) {
				shape[i].y = 39;
			}

			if (shape[i].type == 1) {
				if (mod == false) {
					hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				}
				else if (mod == true) {
					hBrush = CreateSolidBrush(RGB(cr, cg, cb));
				}
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Ellipse(hDC, shape[i].x * length.x, shape[i].y * length.y, (shape[i].x * length.x) + (length.x), (shape[i].y * length.y) + (length.y));
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (shape[i].type == 2) {
				if (mod == false) {
					hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				}
				else if (mod == true) {
					hBrush = CreateSolidBrush(RGB(rr, rg, rb));
				}
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				point[0].x = shape[i].x * length.x;
				point[0].y = shape[i].y * length.y + length.y;
				point[1].x = shape[i].x * length.x + length.x;
				point[1].y = shape[i].y * length.y + length.y;
				point[2].x = shape[i].x * length.x + length.x / 2;
				point[2].y = shape[i].y * length.y;
				point[3].x = shape[i].x * length.x;
				point[3].y = shape[i].y * length.y + length.y;
				Polygon(hDC, point, 4);//삼각형
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (shape[i].type == 3) {
				if (mod == false) {
					hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
				}
				else if (mod == true) {
					hBrush = CreateSolidBrush(RGB(sr, sg, sb));
				}
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, shape[i].x * length.x, shape[i].y * length.y, (shape[i].x * length.x) + (length.x), (shape[i].y * length.y) + (length.y));
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}
		for (int i = 0; i < 10; ++i) {
			if (size == 0 && shape[i].x >= 30) {
				shape[i].x = 29;
			}
			else if (size == 0 && shape[i].y >= 30) {
				shape[i].y = 29;

			}
			if (size == 1 && shape[i].x >= 40) {
				shape[i].x = 39;
			}
			else if (size == 1 && shape[i].y >= 40) {
				shape[i].y = 39;
			}

			if (shape[i].type == 1) {
				if (shape[i].check == true) {
					hPen = CreatePen(PS_DOT, 3, RGB(255, 0, 0));
					if (mod == false) {
						hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
					}
					else if (mod == true) {
						hBrush = CreateSolidBrush(RGB(cr, cg, cb));
					}
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					oldPen = (HPEN)SelectObject(hDC, hPen);
					Ellipse(hDC, shape[i].x * length.x, shape[i].y * length.y, (shape[i].x * length.x) + (length.x), (shape[i].y * length.y) + (length.y));
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
				}
			}
			else if (shape[i].type == 2) {
				if (shape[i].check == true) {
					hPen = CreatePen(PS_DOT, 3, RGB(255, 0, 0));
					if (mod == false) {
						hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
					}
					else if (mod == true) {
						hBrush = CreateSolidBrush(RGB(rr, rg, rb));
					}
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					oldPen = (HPEN)SelectObject(hDC, hPen);
					point[0].x = shape[i].x * length.x;
					point[0].y = shape[i].y * length.y + length.y;
					point[1].x = shape[i].x * length.x + length.x;
					point[1].y = shape[i].y * length.y + length.y;
					point[2].x = shape[i].x * length.x + length.x / 2;
					point[2].y = shape[i].y * length.y;
					point[3].x = shape[i].x * length.x;
					point[3].y = shape[i].y * length.y + length.y;
					Polygon(hDC, point, 4);//삼각형
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
				}
			}
			else if (shape[i].type == 3) {
				if (shape[i].check == true) {
					hPen = CreatePen(PS_DOT, 3, RGB(255, 0, 0));
					if (mod == false) {
						hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
					}
					else if (mod == true) {
						hBrush = CreateSolidBrush(RGB(sr, sg, sb));
					}
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					oldPen = (HPEN)SelectObject(hDC, hPen);
					Rectangle(hDC, shape[i].x * length.x, shape[i].y * length.y, (shape[i].x * length.x) + (length.x), (shape[i].y * length.y) + (length.y));
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
				}
			}
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}