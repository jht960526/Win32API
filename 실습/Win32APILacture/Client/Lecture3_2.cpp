#include <windows.h>
#include <cmath>
#include <stdio.h>
#include "time.h"

//아이템의 랜덤화를 위한 랜덤 함수
int random(int r)
{
    srand((int)time(NULL));
    r = rand() % 3 + 1;
    return r;
}

//아이템을 떨어지게 만드는 구조체
struct itemstruct
{
    bool itemstart;
    int itemx, itemy;
}items[30];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Jeong Hong Tak");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("2018180052정홍택"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 350, 500, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    //dst(충돌체크), move[0]=바, move[1]=공, block(블럭의 RECT), item(아이템의렉트)
    static RECT dst, move[2], block, item;
    static RECT barl, barr;//왼쪽바,오른쪽바 변수
    HBRUSH Brush, oBrush;

    //벽돌 배열
    static int doll[4][11] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0
    };
    static int i, j, r, z, count = 0;//for문에서 쓰이는 변수, 랜덤변수,랜덤대입변수, 카운트
    static int ballspeedx = 7, ballspeedy = 7;
    static int barx = 150, bary = 440;//바의 좌표 값
    static int ballx = 165, bally = 425;//볼의 좌표
    static double ball_x = -1, ball_y = -1;//볼의 방향 값
    static bool ballmove = false;//스페이스바 눌렸을때 스타트
    static char jumsu[100];
    static int jumsucount;


    switch (message)
    {

    case WM_CREATE:
        SetTimer(hwnd, 1, 50, NULL);
        for (i = 0; i <= 30; i++)
        {
            items[i].itemstart = false;
        }

        return 0;

    case WM_TIMER:
        for (i = 0; i <= 30; i++)
        {
            if (items[i].itemstart == true) //아이템 떨어지는 부분
            {
                items[i].itemy += 5;
                InvalidateRect(hwnd, NULL, true);
            }
        }

        //볼 이동
        if (ballmove == true)
        {
            //공이동
            ballx -= ballspeedx * ball_x;
            bally += ballspeedy * ball_y;

            //벽 튕기는 부분
            if (ballx < 0)//왼쪽 벽
            {
                if (ball_x == 2)
                    ball_y = -0.7;
                ball_x = -1;
            }

            if (ballx > 320)//오른쪽 벽
            {
                if (ball_x == 2)
                {
                    ball_x = +0.7;
                }
                ball_x = +1;
            }
            if (bally < 0)//윗면
            {
                if (ball_y == 2)
                {
                    ball_x = -0.7;
                }
                ball_y = +1;
            }
            //죽음
            if (bally > 470)
            {
                SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            }
            InvalidateRect(hwnd, NULL, true);
        }
        return 0;



    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            //스페이스 바 누르기 전의 공이동
            if (ballmove == false)
            {
                ballx -= 5;
                if (ballx <= 14)
                    ballx = 14;
            }
            //바 이동
            barx -= 5;

            if (barx <= 0)
                barx = 1;
            InvalidateRect(hwnd, NULL, true);
            break;

        case VK_RIGHT:
            //스페이스 바 누르기 전의 공이동
            if (ballmove == false)
            {
                ballx += 5;
                if (ballx >= 310)
                    ballx = 310;
            }
            //바 이동
            barx += 5;

            if (barx >= 300)
                barx = 295;
            InvalidateRect(hwnd, NULL, true);
            return 0;

            //SPACE눌렀을때 공 스타트
        case VK_SPACE:
            ballmove = true;
            return 0;

        case 'S':
            ballmove = true;
            return 0;

        case '+':
            ballx += 10;
            PostQuitMessage(0);
            //return 0;
            break;

        case '-':
            ballx -= 10;
            break;

            //ESC키 눌렀을때 빠져나감
        case 'Q':
            SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            return 0;

        case 'q':
            SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            return 0;
        }
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        
       

        //블럭 부분
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 11; j++)
            {
                if (doll[i][j] != 0)
                {
                    SetRect(&block, j * 30, i * 20, j * 30 + 30, i * 20 + 20);
                    //공과 블럭의 충돌체크
                    if (IntersectRect(&dst, &move[1], &block) != 0)
                    {
                        jumsucount += 10;
                        r = random(z);
                        //item충돌 체크
                        if (r == 1 || r == 2 || r == 3)
                        {
                            count++;
                            items[count].itemstart = true;

                            if (items[count].itemstart != false)
                            {
                                items[count].itemx = ballx;
                                items[count].itemy = bally;
                            }
                            doll[i][j] = 0;
                            ball_y = +1;
                        }
                        doll[i][j] = 0;
                        ball_y = +1;
                    }
                }
            }
        }
        Brush = CreateSolidBrush(RGB(30, 150, 20));
        oBrush = (HBRUSH)SelectObject(hdc, Brush);
        //블럭 그리는 부분
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 11; j++)
            {
                if (doll[i][j] != 0)
                {
                    Rectangle(hdc, j * 30, i * 20, j * 30 + 30, i * 20 + 20);
                }
            }
        }
        SelectObject(hdc, oBrush);
        DeleteObject(Brush);
        //왼쪽바
        SetRect(&barl, barx, bary, barx + 5, bary + 10);
        if (IntersectRect(&dst, &barl, &move[1]) != 0)
        {
            ball_x = 2;
            ball_y = -1;
            ballspeedx = 10;
            ballspeedy = 10;
        }

        //오른쪽바
        SetRect(&barr, barx + 45, bary, barx + 50, bary + 10);
        if (IntersectRect(&dst, &barr, &move[1]) != 0)
        {
            ball_x = -2;
            ball_y = -1;
            ballspeedx = 10;
            ballspeedy = 10;
        }


        //바
        Brush = CreateSolidBrush(RGB(100, 200, 230));
        oBrush = (HBRUSH)SelectObject(hdc, Brush);
        SetRect(&move[0], barx + 5, bary, barx + 45, bary + 10);
        Rectangle(hdc, barx, bary, barx + 50, bary + 10);
        SelectObject(hdc, oBrush);
        DeleteObject(Brush);

        //공
        Brush = CreateSolidBrush(RGB(150, 100 , 150));
        oBrush = (HBRUSH)SelectObject(hdc, Brush);
        SetRect(&move[1], ballx, bally, ballx + 15, bally + 15);
        Ellipse(hdc, ballx, bally, ballx + 15, bally + 15);
        SelectObject(hdc, oBrush);
        DeleteObject(Brush);

        //공과 바의 충돌체크
        if (IntersectRect(&dst, &move[0], &move[1]) != 0)
        {
            ballspeedx = 7;
            ballspeedy = 7;
            ball_y = -1;
        }

        //item그리기

       /* for (i = 0; i <= 30; i++)
        {
            if (items[i].itemstart == true)
            {
                Rectangle(hdc, items[i].itemx, items[i].itemy, items[i].itemx + 5, items[i].itemy + 5);
            }
        }*/


        //바와 아이템과의 충돌체크

        for (i = 0; i <= 30; i++)
        {
            if (items[i].itemstart == true)
            {
                SetRect(&item, items[i].itemx, items[i].itemy, items[i].itemx + 5, items[i].itemy + 5);

                if (IntersectRect(&dst, &move[0], &item) != 0)
                {
                    items[i].itemstart = false;
                    jumsucount += 100;
                }

                if (IntersectRect(&dst, &barl, &item) != 0)
                {
                    items[i].itemstart = false;
                    jumsucount += 100;
                }

                if (IntersectRect(&dst, &barr, &item) != 0)
                {
                    items[i].itemstart = false;
                    jumsucount += 100;
                }
            }
        }


        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
