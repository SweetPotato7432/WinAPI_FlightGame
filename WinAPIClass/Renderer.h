#pragma once
#include "framework.h"
#include "Component.h"
#include <vector>
using namespace std;

// 이미지(비트맵) 그리기 클래스
class Renderer : public Component
{
private:
	static vector<Renderer*> renderers;

public:
	static void DrawAll(HDC hdc);

protected:
	HBITMAP hBitmap;

protected:
	SIZE size;
	SIZE halfSize;
	SIZE bmSize;

public:
	void SetSize(int width, int height);
	virtual void Draw(HDC hdc);

public:
	Renderer(int bmId, GameObject& gameObject);
	~Renderer();
};

