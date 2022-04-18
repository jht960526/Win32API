#include <Windows.h>
#include <tchar.h>
#include <ctime>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 3-1";

#define MOVE_TYPE_0 0
#define MOVE_TYPE_1 1

struct MB
{
	int x = 0, y = 0;
	int move = 1;		// 1. 좌, 2. 우, 3. 상, 4.하
	bool tailcheck{};
	bool headcheck{};
	bool tailmove{};
	bool clickcheck{};
	int BS = 1;
	RECT bound{};
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_SYSMENU, 0, 0, 618, 641, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message, 0, 0, 0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static TCHAR wP{};
	static RECT rt{};
	static RECT middle{};
	static MB head[100]{};
	static MB tail[100]{};
	HBRUSH hBrush, oldBrush;
	static int mai = 100;
	static int tailcount = 0;
	static int hCheck = 0;
	static BOOL Movecheck{};
	static POINT length{};
	switch (uMsg)
	{
	case WM_CREATE:
		srand((unsigned int)time(NULL));
		GetClientRect(hWnd, &rt);
		length.x = rt.right / 40;
		length.y = rt.bottom / 40;
		Movecheck = false;
		head[0].headcheck = true;
		for (int i = 0; i < 100; ++i) 
		{
			tail[i].x = -1;
			tail[i].y = -1;
		}
		SetTimer(hWnd, 1, mai, NULL); // 주인공원 타이머

		SetTimer(hWnd, 2, 3000, NULL); // 꼬리원 생성되는 타이머

		SetTimer(hWnd, 3, 500, NULL); // 생성된
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		// 칸 만들기
		for(int i = 0; i < 40; ++i)
		{
			for(int j = 0; j < 40; ++j)
			{
				Rectangle(hDC, i * length.x, j * length.y, (i + 1) * length.x, (j + 1) * length.y);
			}
		}


		for(int i = 0; i < 100; ++i)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Ellipse(hDC, head[i].x * length.x, head[i].y * length.y, (head[i].x * length.x) + (length.x), (head[i].y * length.y) + (length.y));
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);

			if(head[i].headcheck)
			{
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Ellipse(hDC, (head[i].x * length.x) + length.x, head[i].y * length.y, (head[i].x * length.x) + (length.x), (head[i].y * length.y) + (length.y));
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}

			if(tail[i].tailcheck) 
			{
				for(int j = i + 1; j < 100; ++j) 
				{
					if(tail[i].x == tail[j].x && tail[i].y == tail[j].y)
					{
						tail[i].BS = 2;
					}
				}
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Ellipse(hDC, tail[i].x * length.x, tail[i].y * length.y, (tail[i].x * length.x) + (length.x * tail[i].BS), (tail[i].y * length.y) + (length.y * tail[i].BS));
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:
		switch(wParam)
		{
		case 1:
			if(Movecheck) 
			{
				for(int i = 0; i < 100; ++i) 
				{
					if(head[i].move == 1) 
					{
						if (head[i].x == 40) 
						{
							++head[i].y;
							head[i].move = 2;
							if (head[i].y == 40) 
							{
								head[i].x = 0;
								head[i].y = 0;
							}
						}
						else 
						{
							++head[i].x;
						}
					}
					if(head[i].move == 2) 
					{
						if (head[i].x == 0) 
						{
							++head[i].y;
							head[i].move = 1;
							if (head[i].y == 40) 
							{
								head[i].x = 0;
								head[i].y = 0;
							}
						}
						else 
						{
							--head[i].x;
						}
					}
					else if(head[i].move == 3) 
					{
						if (head[i].y == 0) 
						{
							head[i].x++;
							head[i].move = 4;
							if (head[i].x == 40) 
							{
								head[i].x = 0;
								head[i].y = 0;
							}
						}
						else 
						{
							head[i].y--;
						}
					}
					else if(head[i].move == 4) 
					{
						if (head[i].y == 40) 
						{
							head[i].x++;
							head[i].move = 3;
							if (head[i].x == 40) 
							{
								head[i].x = 0;
								head[i].y = 0;
							}
						}
						else 
						{
							head[i].y++;
						}
					}
					if(!head[hCheck].headcheck && tail[i].tailcheck && head[0].x == tail[i].x && head[0].y == tail[i].y) 
					{
						hCheck++;
						head[hCheck].headcheck = true;
						tail[i].tailcheck = false;
						if(head[hCheck - 1].move == 1) 
						{
							head[hCheck].x = --head[hCheck - 1].x;
						}
						else if(head[hCheck - 1].move == 2) 
						{
							head[hCheck].x = ++head[hCheck - 1].x;
						}
						else if(head[hCheck - 1].move == 3) 
						{
							head[hCheck].y = ++head[hCheck - 1].y;
						}
						else if(head[hCheck - 1].move == 4) {
							head[hCheck].x = --head[hCheck - 1].y;
						}
					}
				}
			}

			break;
		case 2:
			if(Movecheck) 
			{
				tail[tailcount].tailcheck = true;
				tail[tailcount].x = rand() % 30 + 10;
				tail[tailcount].y = rand() % 30 + 10;
				tail[tailcount].tailmove = 0;
				tail[tailcount].move = rand() % 4 + 1;
				++tailcount;
			}
			break;
		case 3:
			if(Movecheck) 
			{
				for(int i = 0; i < 100; ++i) 
				{
					if(tail[i].tailcheck) 
					{
						if(tail[i].tailmove == MOVE_TYPE_0) 
						{
							if(tail[i].move == 1)
							{
								if(tail[i].x == 39) 
								{
									tail[i].move = (rand() % 3) + 2;
								}
								else 
								{
									++tail[i].x;
								}
							}
							else if(tail[i].move == 2) 
							{
								if (tail[i].x == 0) 
								{
									tail[i].move = rand() % 4 + 1;
								}
								else 
								{
									--tail[i].x;
								}
							}
							else if(tail[i].move == 3)
							{
								if(tail[i].y == 0) 
								{
									tail[i].move = rand() % 4 + 1;
								}
								else 
								{
									tail[i].y--;
								}
							}
							else if(tail[i].move == 4) 
							{
								if(tail[i].y == 39) 
								{
									tail[i].move = rand() % 4 + 1;
								}
								else 
								{
									tail[i].y++;
								}
							}
						}
						/*else if(tail[i].tailmove == MOVE_TYPE_1) 
						{
							if (tail[i].tailcheck) 
							{

							}
						}*/
					}
				}
			}
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_KEYUP:
		wP = wParam;
		switch (wP)
		{
		case 's':
			Movecheck = true;
			break;
		case 'S':
			Movecheck = true;
			break;
		case '+':
			break;
		case '-':
			break;
		case 'q':
			PostQuitMessage(0);
			break;

		case 'Q':
			PostQuitMessage(0);
			break;

		case VK_UP:
			for(int i = 0; i < 100; ++i) 
			{
				head[i].move = 3;
			}
			break;
		case VK_DOWN:
			for(int i = 0; i < 100; ++i) 
			{
				head[i].move = 4;
			}
			break;
		case VK_RIGHT:
			for(int i = 0; i < 100; ++i) 
			{
				head[i].move = 1;
			}
			break;
		case VK_LEFT:
			for(int i = 0; i < 100; ++i) 
			{
				head[i].move = 2;
			}
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}