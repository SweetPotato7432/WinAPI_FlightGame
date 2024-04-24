#include "Application.h"

Application* Application::instance = nullptr;

LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return instance->MsgProc(hWnd, message, wParam, lParam);
}

ATOM Application::RegisterWindow(HINSTANCE hInstance)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPICLASS, szWindowClass, MAX_LOADSTRING);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPICLASS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPICLASS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL Application::Initiate(int nCmdShow)
{
    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

int Application::MessageLoop()
{
    MSG msg;

    //// �⺻ �޽��� �����Դϴ�:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{

    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);

    //}
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    
    return (int)msg.wParam;
}

LRESULT Application::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                // �޴� ������ ���� �м��մϴ�:
                switch (wmId)
                {
                    case IDM_ABOUT:
                        //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        break;
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_SIZE : 
            {
                int width = LOWORD(lParam);
                int height = HIWORD(lParam);

                graphic.SetSize(width, height);
            }
            break;
        case WM_PAINT:
            {
                HDC hdc = graphic.StartDraw(hWnd);

                // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

                graphic.EndDraw();

            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

Application::Application()
{
    if (!instance)
        instance = this;
}
