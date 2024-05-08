#include "Application.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Background.h"
#include "Time.h"
#include "Plane.h"
#include "Bullet.h"
#include "Animation.h"
#include "Input.h"

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
    RECT wndRect = { 0,0,resolution.cx,resolution.cy };
    // 윈도우의 너비, 높이는 메뉴바, 제목표시줄을 포함한 크기이다.
    // 그러므로 해상도에 맞춰 출력영역을 생성하려면 해상도 보다 조금 더 넓게 윈도우를 생성해주어야 한다.
    // AdjsutWindowRect : 출력 영역의 크기를 맞출 수 있도록 윈도우의 크기(메뉴, 제목 표시줄 등을 포함한...)를 계산해주는 함수
    AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, TRUE);

    // 계산한 후 왼쪽 위 좌표가 0,0이 아니므로 실제 길이를 계산하려면 빼주어야 한다.
    int width = wndRect.right - wndRect.left;
    int height = wndRect.bottom - wndRect.top;

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInst, nullptr);

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

        Time::Update();

        // 매 프레임 마다 게임 오브젝트를 업데이트
        GameObject::EventUpdate();
        Animation::EventUpdate();

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
        Time::Start();

        // 게임 오브젝트에 주소 저장, 해제를 모두 한다.
        Background* bg[2];
        bg[0] = new Background;
        bg[0]->SetPosition({ defaultResolution.cx * 0.5f,defaultResolution.cy * 0.5f });
        // 두번째 배경을 이어 붙인다.
        bg[1] = new Background;
        bg[1]->SetPosition({ defaultResolution.cx * 1.5f,defaultResolution.cy * 0.5f });

        Plane* plane = new Plane;
        plane->SetPosition({ 200.0f,400.0f });


    }
    break;
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        //wParam : 누른 키 정보
        // 누를때 true, 뗄때 false로 설정
        Input::SetKey(wParam, message == WM_KEYDOWN);
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
    case WM_SIZE: // 윈도우의 크기가 변경되었을때 발생하는 메시지
    {
        resolution.cx = LOWORD(lParam);
        resolution.cy = HIWORD(lParam);

        // 비율 계산
        ratio.x = resolution.cx * inverseResolution.x;
        ratio.y = resolution.cy * inverseResolution.y;

        graphic.SetSize(resolution.cx, resolution.cy);
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

const SIZE& Application::GetDefaultResolution()
{
    return instance->defaultResolution;
}

const Vector2& Application::GetRatio()
{
    return instance->ratio;
}

Application::Application()
    : defaultResolution({ 1600,900 }),
    inverseResolution({ 1.0f / 1600.0f ,1.0f / 900.0f }),
    ratio({ 1.0f,1.0f })
{
    if (!instance)
        instance = this;
    // 현재 해상도를 기본 해상도로
    resolution = defaultResolution;
}
