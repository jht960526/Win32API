#include <windows.h>
#include <tchar.h>

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Program 1";

LRESULT CALLBACK WndProc (HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct BALL
{
	int x = 0,y = 0;
};

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
	WndClass.hIcon = LoadIcon(nullptr,IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(nullptr,IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = nullptr;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(nullptr,IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, nullptr, (HMENU)nullptr, hInstance, nullptr);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message,0,0,0))
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

    HBRUSH hbrush, oldBrush;

    static int Timer1Count = 0, Timer2Count = 0;
    static int x = 0, y;
    static RECT rectView;
    static RECT Graph;
    static POINT Length{};
    static BALL HeadBall[100] {};

	// 메시지 처리하기
	switch (iMessage)
	{
	case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        GetClientRect(hWnd, &Graph);
        x = 0;
        y = 0;

        Length.x = Graph.right/40;
        Length.y = Graph.bottom/40;

        //SetTimer(hWnd, 1, 60, NULL);
		//SetTimer(hWnd, 2, 100, NULL);
        SetTimer(hWnd,1,100,NULL);

		break;

	case WM_PAINT:
        Hdc = BeginPaint(hWnd,&ps);

        // 칸 만들기
        for(int i = 0; i < 40; ++i)
        {
	        for(int j = 0; j < 40; ++j)
	        {
		        Rectangle(Hdc,i * Length.x, j * Length.y, (i + 1) * Length.x, (j + 1) * Length.y);
	        }
        }

        for(int i = 0; i < 100; ++i)
        {
	        hbrush = CreateSolidBrush(RGB(0, 255, 0));
        	oldBrush = (HBRUSH)SelectObject(Hdc, hbrush);
        	Ellipse(Hdc, HeadBall[i].x * Length.x, HeadBall[i].y * Length.y,(HeadBall[i].x * Length.x) + Length.x, (HeadBall[i].y * Length.y) + Length.y);
        	SelectObject(Hdc, oldBrush);
        	DeleteObject(hbrush);
        }

        

        EndPaint(hWnd, &ps);
		break;

    case WM_KEYDOWN:
        
        switch (wParam)
        {
        case 's':
            SetTimer(hWnd, 1, 100, NULL);
            break;

        case 'S':
            SetTimer(hWnd, 1, 100, NULL);
            break;

        case 'Q':
            PostQuitMessage(0);
            return 0;

        case 'q':
            PostQuitMessage(0);
            return 0;
        }

        break;

    case WM_TIMER:

        for(int i = 0; i < 100; ++i)
        {
	        HeadBall[i].x += HeadBall[i].x;
        }

        x += 40;
        if (x + 20 > rectView.right)
        {
            x = 0;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;


	case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
		break;
	}

	// 이외의 메세지는 OS로
	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}
