#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class name";
LPCTSTR lpszWindowName = L"Window Programming 2-9";
LRESULT CALLBACK wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASSEX WndClass;
    g_hInst = hInstance;
    WndClass.cbSize = sizeof(WndClass);
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = (WNDPROC)wndProc;
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

LRESULT CALLBACK wndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static TCHAR str[100];
    static int count = 0;
    PAINTSTRUCT ps;
    HPEN hPen, oldPen;
    HBRUSH hbr, oldBrush;

    srand(time(NULL));

    static int mod;
    static int x1;
    static int y1;
    static int x2;
    static int y2;
    static int n; //�β�

    static int a;
    static int ck;
    static int c;

    switch (iMsg) {
    case WM_CREATE:
        mod = 0;
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        a = 0;
        n = 0;
        ck = 0;
        count = 0;
        c = 1;

        break;
    case WM_KEYDOWN:
        if (wParam == VK_LEFT) {
            --x1;
            --x2;
            InvalidateRect(hwnd, NULL, true);
        }
        else if (wParam == VK_RIGHT) {
            ++x1;
            ++x2;
            InvalidateRect(hwnd, NULL, true);
        }
        else if (wParam == VK_UP) {
            --y1;
            --y2;
            InvalidateRect(hwnd, NULL, true);
        }
        else if (wParam == VK_DOWN) {
            ++y1;
            ++y2;
            InvalidateRect(hwnd, NULL, true);
        }

        if (wParam == '+') {
            ++n;
            InvalidateRect(hwnd, NULL, true);
        }
        else if (wParam == '-') {
            --n;
            InvalidateRect(hwnd, NULL, true);
        }
       
        break;
    case WM_CHAR: //--- 1�������� ���ڿ��� ���
        hdc = GetDC(hwnd);

        str[count++] = wParam;
        //str[count] = '\0';

        if (str[count - 1] == VK_SPACE) {
            if (ck == 0) {
                mod = _wtoi(str);
                ++ck;
                a = count;
            }
            else if (ck == 1) {
                x1 = _wtoi(str + (a));
                ++ck;
                a = count;
            }
            else if (ck == 2) {
                y1 = _wtoi(str + (a));
                ++ck;
                a = count;
            }
            else if (ck == 3) {
                x2 = _wtoi(str + (a));
                ++ck;
                a = count;
            }
            else if (ck == 4) {
                y2 = _wtoi(str + (a));
                ++ck;
                a = count;
            }
        }
        else if (str[count - 1] == VK_RETURN) {
            if (ck == 5) {
                n = _wtoi(str + (a));
                ++ck;
            }
            c = 0;
            for (int i = 0; i < lstrlen(str); ++i) {
                str[i] = { '\0' };
            }
            count = 0;
        }
        else if (str[count - 1] == VK_BACK) {
            count--;
        }
     
      //=== �ߺ�

        InvalidateRect(hwnd, NULL, true);

        break;

    case WM_PAINT: //--- ȭ���� ���ȴ� �������� �ٽ� ���ڿ��� ���
        hdc = BeginPaint(hwnd, &ps);

        hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // GDI: �� �����
        hbr = (HBRUSH)GetStockObject(RGB(0, 0, 0));
        oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� �����ϱ�
        oldBrush = (HBRUSH)SelectObject(hdc, hbr);
        Rectangle(hdc, 1, 635, 780, 660); // ������ ������ ���� �׸���
        SelectObject(hdc, oldPen); // ������ ������ ���ư�   
        DeleteObject(hbr);
       

        if (mod == 1) {
            hPen = CreatePen(PS_SOLID, n, RGB(rand() % 255, rand() % 255, rand() % 255));
            oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)hPen);
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);

        }
        else if (mod == 2) {
            hPen = CreatePen(PS_SOLID, n, RGB(0, 0, 0)); // GDI: �� �����
            hbr = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
            oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� �����ϱ�
            oldBrush = (HBRUSH)SelectObject(hdc, hbr);

            POINT point3[10] = { {(x1 + x2) / 2, y1}, {x1, y2}, {x2, y2} };

            Polygon(hdc, point3, 3);
            SelectObject(hdc, oldPen);
        }
        else if (mod == 3) {
            hPen = CreatePen(PS_SOLID, n, RGB(0, 0, 0)); // GDI: �� �����
            hbr = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
            oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� �����ϱ�
            oldBrush = (HBRUSH)SelectObject(hdc, hbr);
            Rectangle(hdc, x1, y1, x2, y2); // ������ ������ ���� �׸���
            SelectObject(hdc, oldPen);
        }
        else if (mod == 4) {
            hPen = CreatePen(PS_SOLID, n, RGB(0, 0, 0)); // GDI: �� �����
            hbr = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
            oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� �����ϱ�
            oldBrush = (HBRUSH)SelectObject(hdc, hbr);
            Ellipse(hdc, x1, y1, x2, y2); // ������ ������ ���� �׸���
            SelectObject(hdc, oldPen);
        }
        TextOut(hdc, 5, 640, str, lstrlen(str));
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}