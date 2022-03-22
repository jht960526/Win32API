#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class name";
LPCTSTR lpszWindowName = L"Window Programming 2-3";
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
        0, 0, 700, 650, NULL, (HMENU)NULL, hInstance, NULL);
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
    static TCHAR str[100] = { 0 };
    static TCHAR gugudan[50] = { 0 };
    static int count;

    static int x;
    static int y;
    static int N;
    static int a;
    static int ck;
    static int c;

    switch (iMsg) {
    case WM_CREATE:
        CreateCaret(hwnd, NULL, 5, 15);
        ShowCaret(hwnd);
        x = 0;
        y = 0;
        N = 0;
        a = 0;
        ck = 0;
        count = 0;
        c = 1;

        break;
    case WM_CHAR:
        str[count++] = wParam;
        str[count] = '\0';

        if (str[count - 1] == VK_SPACE) {
            if (ck == 0) {
                x = _wtoi(str);
                ++ck;
                a = count;
            }
            else if (ck == 1) {
                y = _wtoi(str + (a));
                ++ck;
            }
        }
        else if (str[count - 1] == VK_RETURN) {
            if (ck == 2) {
                N = _wtoi(str + (count - 3));
                ++ck;
            }
            c = 0;
            for (int i = 0; i < lstrlen(str); ++i) {
                str[i] = {};
            }

            count = 0;
        }
        else if (str[count - 1] == VK_BACK) {
            count--;
        }
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetTextExtentPoint32(hdc, str, lstrlen(str), &size); //--- 문자열 길이 알아내기
        if (c == 0) {
            for (int i = 1; i <= 9; ++i) {
                wsprintf(gugudan, L"%dx%d=%d ", N, i, N * i);
                if (i == 6) {
                    y += 20;
                    x -= 300;
                }
                TextOut(hdc, x, y, gugudan, lstrlen(gugudan));
                x += 60;
            }
            x = 0;
            y = 0;
            N = 0;
            a = 0;
            ck = 0;
            c = 1;
        }
        else {
            TextOut(hdc, 0, 0, str, lstrlen(str));

        }
        SetCaretPos(size.cx, 0); //--- 캐럿 위치하기
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        HideCaret(hwnd); //--- 캐럿 숨기기
        DestroyCaret(); //--- 캐럿 삭제하기
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}