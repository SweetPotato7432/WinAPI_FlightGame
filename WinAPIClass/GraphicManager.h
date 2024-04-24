#pragma once
#include "framework.h"

class GraphicManager
{
private : 
	HWND hWnd;
	PAINTSTRUCT ps;
	HDC hdc, memDC;
	HBITMAP hBitmap;

private : 
	int width, height;

public :
	void SetSize(int widht, int height);
	HDC StartDraw(HWND hWnd);
	void EndDraw();

public : 
	GraphicManager();
	~GraphicManager() = default;
};

