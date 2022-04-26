#include <Windows.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;

    WNDCLASS WndClass;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = _T("Window Class Name");

    RegisterClass(&WndClass); //������ Ŭ������ Ŀ�ο� ���

    hwnd = CreateWindow( //������ �ڵ鰪 ��ȯ
        _T("Window Class Name"), //������ Ŭ���� �̸�
        _T("ȫ�浿�� ù ��° ������"), //������ Ÿ��Ʋ�̸�
        WS_OVERLAPPEDWINDOW, //������ ��Ÿ��
        100, //������ ��ġ x��ǥ
        100,//������ ��ġ y��ǥ
        1000, //������ ����ũ��
        1000, //������ ����ũ��
        NULL, //�θ� �������ڵ�
        NULL, //�޴��ڵ�
        hInstance, //�������α׷� �ν��Ͻ�
        NULL); //���� ������ ����

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int headX = 60, headY = 20;
    static int tailX = 20, tailY = 20;

    static RECT rectView;
    static bool isGoing = false;
    static int Direction = 1;
    HPEN hPen, oldPen;

    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &rectView); //������ Ŭ���̾�Ʈ ������ ����� RECT������ ����
        break;

    case WM_KEYDOWN:
        if (wParam == VK_RIGHT && (tailX + 60) <= 600)
        {
            headX = tailX + 40;
            headY = tailY;
            Direction = 1;
        }
        else if (wParam == VK_LEFT && (tailX - 60) >= 0)
        {
            headX = tailX - 40;
            headY = tailY;
            Direction = 3;
        }
        else if (wParam == VK_UP && (tailY - 60) >= 0)
        {
            headX = tailX;
            headY = tailY - 40;
            Direction = 4;
        }
        else if (wParam == VK_DOWN && (tailY + 60) <= 600)
        {
            headX = tailX;
            headY = tailY + 40;
            Direction = 2;
        }
        if (wParam == VK_RETURN)
        {
            if (isGoing) isGoing = false;
            else isGoing = true;

            if (isGoing)
                SetTimer(hwnd, 1, 10, NULL);
            else
                KillTimer(hwnd, 1);
            InvalidateRgn(hwnd, NULL, TRUE);
            break;
        }
        InvalidateRgn(hwnd, NULL, TRUE);
        break;

    case WM_TIMER:
        if (Direction == 1 && (headX + 20) < 600) //����
        {
            headX += 2;
            tailX = headX - 40;
        }
        else if (Direction == 3 && (headX - 20) > 0) //��
        {
            headX -= 2;
            tailX = headX + 40;
        }
        else if (Direction == 4 && (headY - 20) > 0) //��
        {
            headY -= 2;
            tailY = headY + 40;
        }
        else if (Direction == 2 && (headY + 20) < 600) //�Ʒ�
        {
            headY += 2;
            tailY = headY - 40;
        }
        InvalidateRgn(hwnd, NULL, TRUE);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        Rectangle(hdc, 0, 0, 600, 600);

        hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //�Ӹ�
        oldPen = (HPEN)SelectObject(hdc, hPen);
        Ellipse(hdc, headX - 20, headY - 20, headX + 20, headY + 20);
        SelectObject(hdc, oldPen);

        hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); //����
        oldPen = (HPEN)SelectObject(hdc, hPen);
        Ellipse(hdc, tailX - 20, tailY - 20, tailX + 20, tailY + 20);
        SelectObject(hdc, oldPen);


        DeleteObject(hPen);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}