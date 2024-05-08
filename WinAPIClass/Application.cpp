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
    RECT wndRect = { 0,0,resolution.cx,resolution.cy };
    // �������� �ʺ�, ���̴� �޴���, ����ǥ������ ������ ũ���̴�.
    // �׷��Ƿ� �ػ󵵿� ���� ��¿����� �����Ϸ��� �ػ� ���� ���� �� �а� �����츦 �������־�� �Ѵ�.
    // AdjsutWindowRect : ��� ������ ũ�⸦ ���� �� �ֵ��� �������� ũ��(�޴�, ���� ǥ���� ���� ������...)�� ������ִ� �Լ�
    AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, TRUE);

    // ����� �� ���� �� ��ǥ�� 0,0�� �ƴϹǷ� ���� ���̸� ����Ϸ��� ���־�� �Ѵ�.
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

    //// �⺻ �޽��� �����Դϴ�:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{

    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);

    //}

    // �޽��� ������ ���� ���� ��� �ٽ� �׸���, ���� �޽����� ���� ����
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Time::Update();

        // �� ������ ���� ���� ������Ʈ�� ������Ʈ
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

        // ���� ������Ʈ�� �ּ� ����, ������ ��� �Ѵ�.
        Background* bg[2];
        bg[0] = new Background;
        bg[0]->SetPosition({ defaultResolution.cx * 0.5f,defaultResolution.cy * 0.5f });
        // �ι�° ����� �̾� ���δ�.
        bg[1] = new Background;
        bg[1]->SetPosition({ defaultResolution.cx * 1.5f,defaultResolution.cy * 0.5f });

        Plane* plane = new Plane;
        plane->SetPosition({ 200.0f,400.0f });


    }
    break;
    case WM_KEYDOWN:
    case WM_KEYUP:
    {
        //wParam : ���� Ű ����
        // ������ true, ���� false�� ����
        Input::SetKey(wParam, message == WM_KEYDOWN);
    }
    break;
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
    case WM_SIZE: // �������� ũ�Ⱑ ����Ǿ����� �߻��ϴ� �޽���
    {
        resolution.cx = LOWORD(lParam);
        resolution.cy = HIWORD(lParam);

        // ���� ���
        ratio.x = resolution.cx * inverseResolution.x;
        ratio.y = resolution.cy * inverseResolution.y;

        graphic.SetSize(resolution.cx, resolution.cy);
    }
    break;
    case WM_PAINT:
    {
        HDC hdc = graphic.StartDraw(hWnd);

        // ��� �׸��� �׸�
        Renderer::DrawAll(hdc);

        graphic.EndDraw();

    }
    break;
    case WM_DESTROY:
    {
        // ��� ���� ������Ʈ�� ����
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
    // ���� �ػ󵵸� �⺻ �ػ󵵷�
    resolution = defaultResolution;
}
