#include "GraphicManager.h"

void GraphicManager::SetSize(int width, int heigth)
{
    this->width = width;
    this->height = heigth;
}

HDC GraphicManager::StartDraw(HWND hWnd)
{
    this->hWnd = hWnd;
    hdc = BeginPaint(hWnd, &ps);

    memDC = CreateCompatibleDC(hdc);
    hBitmap = CreateCompatibleBitmap(hdc, width, height);

    SelectObject(memDC, hBitmap);

    RECT clientRect = { 0,0,width,height };

    FillRect(memDC, &clientRect, (HBRUSH)COLOR_WINDOW);

    return memDC;
}

void GraphicManager::EndDraw()
{
    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

    DeleteObject(hBitmap);
    DeleteDC(memDC);

    EndPaint(hWnd, &ps);
}

GraphicManager::GraphicManager()
    :width(0), height(0)
{
}
