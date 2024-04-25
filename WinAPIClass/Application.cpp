#include "Application.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Background.h"

Application* Application::instance = nullptr;

LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return instance->MsgProc(hWnd, message, wParam, lParam);
}

ATOM Application::RegisterWindow(HINSTANCE hInstance)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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

    //// 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{

    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);

    //}

    // 메시지 유무와 관계 없이 계속 다시 그린다, 종료 메시지가 오면 종료
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // 매 프레임 마다 게임 오브젝트를 업데이트
        GameObject::EventUpdate();

        InvalidateRect(hWnd, NULL, FALSE);
    }
    
    return (int)msg.wParam;
}

LRESULT Application::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 게임 오브젝트에 주소 저장, 해제를 모두 한다.
        new Background;
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        graphic.SetSize(width, height);
    }
    break;
    case WM_PAINT:
    {
        HDC hdc = graphic.StartDraw(hWnd);

        // 모든 그림을 그림
        Renderer::DrawAll(hdc);

        graphic.EndDraw();

    }
    break;
    case WM_DESTROY:
    {
        // 모든 게임 오브젝트를 해제
        GameObject::EventQuit();
        PostQuitMessage(0);
    }

    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HINSTANCE Application::GetInstanceHandle()
{
    return instance->hInst;
}

Application::Application()
{
    if (!instance)
        instance = this;
}
