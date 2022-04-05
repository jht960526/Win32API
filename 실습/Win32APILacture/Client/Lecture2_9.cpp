#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

int turn = 0;
int board[15][15];

int R1 = 0;
int G1 = 255;
int B1 = 0;

int R2 = 0;
int G2 = 0;
int B2 = 255;

int Size1 = 10;
int Size2 = 10;

bool check = false;

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
		0, 0, 1200, 1000, NULL, (HMENU)NULL, hInstance, NULL);
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

	if (check == false) {
		for (int i = 0; i < 15; ++i) {
			for (int a = 0; a < 15; ++a) {
				board[i][a] = 0;
			}
		}

		board[0][0] = 1; //player 1
		board[14][14] = 2; //player 2

		for (int i = 0; i < 16; ++i) {
			int a = rand() % 14;
			int b = rand() % 14;
			if (board[a][b] == 0) {
				board[a][b] = 3; //장애물
			}
			else {
				--i;
			}
		}

		for (int i = 0; i < 4; ++i) {
			int a = rand() % 14;
			int b = rand() % 14;
			if (board[a][b] == 0) {
				board[a][b] = 4; //색상변화
			}
			else {
				--i;
			}
		}

		for (int i = 0; i < 4; ++i) {
			int a = rand() % 14;
			int b = rand() % 14;
			if (board[a][b] == 0) {
				board[a][b] = 5; //크기변화
			}
			else {
				--i;
			}
		}
		check = true;
	}
	switch (iMsg) {
	case WM_CREATE:
		//srand(time(NULL));

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdc = GetDC(hwnd);

		for (int i = 0; i < 16; ++i) {
			MoveToEx(hdc, 50 + i * 50, 50, NULL);
			LineTo(hdc, i * 50 + 50, 800);
		}
		for (int i = 0; i < 16; ++i) {
			MoveToEx(hdc, 50, i * 50 + 50, NULL);
			LineTo(hdc, 800, 50 * i + 50);
		}

		for (int i = 0; i < 15; ++i) {
			for (int a = 0; a < 15; ++a) {
				if (board[i][a] == 1) {
					hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
					hbr = CreateSolidBrush(RGB(R1, G1, B1));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
					oldBrush = (HBRUSH)SelectObject(hdc, hbr);
					Rectangle(hdc, (i + 1) * 50 + Size1, (a + 1) * 50 + Size1, (i + 2) * 50 - Size1, (a + 2) * 50 - Size1); // 선택한 펜으로 도형 그리기

					SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
				}
				else if (board[i][a] == 2) {
					hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
					hbr = CreateSolidBrush(RGB(R2, G2, B2));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
					oldBrush = (HBRUSH)SelectObject(hdc, hbr);
					Rectangle(hdc, (i + 1) * 50 + Size2, (a + 1) * 50 + Size2, (i + 2) * 50 - Size2, (a + 2) * 50 - Size2); // 선택한 펜으로 도형 그리기

					SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
				}
				else if (board[i][a] == 3) {
					hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
					hbr = CreateSolidBrush(RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
					oldBrush = (HBRUSH)SelectObject(hdc, hbr);
					Rectangle(hdc, (i + 1) * 50 + 2, (a + 1) * 50 + 2, (i + 2) * 50 - 1, (a + 2) * 50 - 1); // 선택한 펜으로 도형 그리기

					SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
				}
				else if (board[i][a] == 4) {
					hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
					hbr = CreateSolidBrush(RGB(255, 255, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
					oldBrush = (HBRUSH)SelectObject(hdc, hbr);
					Rectangle(hdc, (i + 1) * 50 + 2, (a + 1) * 50 + 2, (i + 2) * 50 - 1, (a + 2) * 50 - 1); // 선택한 펜으로 도형 그리기

					SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
				}
				else if (board[i][a] == 5) {
					hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: 펜 만들기
					hbr = CreateSolidBrush(RGB(255, 0, 255));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 선택하기
					oldBrush = (HBRUSH)SelectObject(hdc, hbr);
					Rectangle(hdc, (i + 1) * 50 + 2, (a + 1) * 50 + 2, (i + 2) * 50 - 1, (a + 2) * 50 - 1); // 선택한 펜으로 도형 그리기

					SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
				}
			}
		}

		EndPaint(hwnd, &ps); // DC 해제하기
		break;

	case WM_KEYDOWN:
		if (turn == 0) {
			if (wParam == 'A') {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 1 && i != 0 && board[i - 1][a] == 0) {
							board[i][a] = 0;
							board[i - 1][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[14][a] == 0) {
							board[i][a] = 0;
							board[14][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i - 1][a] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i - 1][a] == 4) {
							board[i][a] = 0;
							board[i - 1][a] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i - 1][a] == 5) {
							board[i][a] = 0;
							board[i - 1][a] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i - 1][a] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[14][a] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[14][a] == 4) {
							board[i][a] = 0;
							board[14][a] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[14][a] == 5) {
							board[i][a] = 0;
							board[14][a] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[14][a] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 1;
					}
				}
			}
			else if (wParam == 'D') {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 1 && i != 14 && board[i + 1][a] == 0) {
							board[i][a] = 0;
							board[i + 1][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 14 && board[0][a] == 0) {
							board[i][a] = 0;
							board[0][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 14 && board[i + 1][a] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i + 1][a] == 4) {
							board[i][a] = 0;
							board[i + 1][a] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i + 1][a] == 5) {
							board[i][a] = 0;
							board[i + 1][a] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i != 0 && board[i + 1][a] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[0][a] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[0][a] == 4) {
							board[i][a] = 0;
							board[0][a] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && i == 0 && board[0][a] == 5) {
							board[i][a] = 0;
							board[0][a] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[0][a] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 1;
					}
				}
			}
			else if (wParam == 'W') {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 1 && a != 0 && board[i][a - 1] == 0) {
							board[i][a] = 0;
							board[i][a - 1] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[i][14] == 0) {
							board[i][a] = 0;
							board[i][14] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a - 1] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a - 1] == 4) {
							board[i][a] = 0;
							board[i][a - 1] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a - 1] == 5) {
							board[i][a] = 0;
							board[i][a - 1] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a - 1] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[i][14] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[i][14] == 4) {
							board[i][a] = 0;
							board[i][14] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[i][14] == 5) {
							board[i][a] = 0;
							board[i][14] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 0 && board[i][14] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 1;
					}
				}
			}
			else if (wParam == 'S') {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 1 && a != 14 && board[i][a + 1] == 0) {
							board[i][a] = 0;
							board[i][a + 1] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 14 && board[i][0] == 0) {
							board[i][a] = 0;
							board[i][0] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a + 1] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a + 1] == 4) {
							board[i][a] = 0;
							board[i][a + 1] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a + 1] == 5) {
							board[i][a] = 0;
							board[i][a + 1] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a != 0 && board[i][a + 1] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 14 && board[i][0] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 14 && board[i][0] == 4) {
							board[i][a] = 0;
							board[i][0] = 1;
							R1 = 255;
							G1 = 255;
							B1 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 14 && board[i][0] == 5) {
							board[i][a] = 0;
							board[i][0] = 1;
							if (Size1 == 10) {
								Size1 = 5;
							}
							else if (Size1 == 5) {
								Size1 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 1 && a == 14 && board[i][0] == 2) {
							MessageBox(hwnd, L"Player 1 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 1;
					}
				}
			}
			else if (wParam == VK_LEFT) {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"Error", MB_OK);
				return 0;
			}
			else if (wParam == VK_RIGHT) {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
			else if (wParam == VK_UP) {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
			else if (wParam == VK_DOWN) {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
		}
		else if (turn == 1) {
			if (wParam == VK_LEFT) {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 0) {
							board[i][a] = 0;
							board[i - 1][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[14][a] == 0) {
							board[i][a] = 0;
							board[14][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 4) {
							board[i][a] = 0;
							board[i - 1][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 5) {
							board[i][a] = 0;
							board[i - 1][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 1) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[14][a] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[14][a] == 4) {
							board[i][a] = 0;
							board[14][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[14][a] == 5) {
							board[i][a] = 0;
							board[14][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 1) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 0;
					}
				}
			}
			else if (wParam == VK_RIGHT) {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 2 && i != 14 && board[i + 1][a] == 0) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 14 && board[0][a] == 0) {
							board[i][a] = 0;
							board[0][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 14 && board[i + 1][a] == 3) {
							board[i][a] = 1;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i + 1][a] == 4) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i + 1][a] == 5) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i + 1][a] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 4) {
							board[i][a] = 0;
							board[0][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 5) {
							board[i][a] = 0;
							board[0][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[0][a] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 0;
					}
				}
			}
			else if (wParam == VK_RIGHT) {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 2 && i != 14 && board[i + 1][a] == 0) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 14 && board[0][a] == 0) {
							board[i][a] = 0;
							board[0][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 14 && board[i + 1][a] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i - 1][a] == 4) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i + 1][a] == 5) {
							board[i][a] = 0;
							board[i + 1][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i != 0 && board[i + 1][a] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 4) {
							board[i][a] = 0;
							board[0][a] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && i == 0 && board[0][a] == 5) {
							board[i][a] = 0;
							board[0][a] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[0][a] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 0;
					}
				}
			}
			else if (wParam == VK_UP) {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 2 && a != 0 && board[i][a - 1] == 0) {
							board[i][a] = 0;
							board[i][a - 1] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 0) {
							board[i][a] = 0;
							board[i][14] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a - 1] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a - 1] == 4) {
							board[i][a] = 0;
							board[i][a - 1] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a - 1] == 5) {
							board[i][a] = 0;
							board[i][a - 1] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a - 1] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 4) {
							board[i][a] = 0;
							board[i][14] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 5) {
							board[i][a] = 0;
							board[i][14] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 0 && board[i][14] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 0;
					}
				}
			}
			else if (wParam == VK_DOWN) {
				for (int i = 0; i < 15; ++i) {
					for (int a = 0; a < 15; ++a) {
						if (board[i][a] == 2 && a != 14 && board[i][a + 1] == 0) {
							board[i][a] = 0;
							board[i][a + 1] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 14 && board[i][0] == 0) {
							board[i][a] = 0;
							board[i][0] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a + 1] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a + 1] == 4) {
							board[i][a] = 0;
							board[i][a + 1] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a + 1] == 5) {
							board[i][a] = 0;
							board[i][a + 1] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size1 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a != 0 && board[i][a + 1] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 14 && board[i][0] == 3) {
							board[i][a] = 2;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 14 && board[i][0] == 4) {
							board[i][a] = 0;
							board[i][0] = 2;
							R2 = 255;
							G2 = 255;
							B2 = 0;
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 14 && board[i][0] == 5) {
							board[i][a] = 0;
							board[i][0] = 2;
							if (Size2 == 10) {
								Size2 = 5;
							}
							else if (Size2 == 5) {
								Size2 = 10;
							}
							i = 15;
							a = 15;
						}
						else if (board[i][a] == 2 && a == 14 && board[i][0] == 2) {
							MessageBox(hwnd, L"Player 2 Win.", L"Quit", MB_OK);
							PostQuitMessage(0);
							//상대 말을 잡은 경우
							i = 15;
							a = 15;
						}
						turn = 0;
					}
				}
			}
			else if (wParam == 'A' || wParam == 'a') {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"Error", MB_OK);
				return 0;
			}
			else if (wParam == 'S' || wParam == 's') {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
			else if (wParam == 'D' || wParam == 'd') {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
			else if (wParam == 'W' || wParam == 'w') {
				MessageBox(hwnd, L"현재 자신의 턴이 아닙니다.", L"메시지 박스", MB_OK);
				return 0;
			}
		}
		if (wParam == 'Q' || wParam == 'q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'R' || wParam == 'r') {
			check = false;
		}


		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}