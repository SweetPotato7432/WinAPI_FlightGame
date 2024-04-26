#include "Renderer.h"
#include "GameObject.h"
#include "Application.h"

vector<Renderer*> Renderer::renderers;

void Renderer::DrawAll(HDC hdc)
{
	int length = renderers.size();
	for (int i = 0; i < length; i++) {
		Renderer& temp = *renderers[i];
		if (temp.active) {
			temp.Draw(hdc);
		}
	}
}

void Renderer::SetSize(int width, int height)
{
	size.cx = width;
	size.cy = height;

	halfSize.cx = width >> 1;
	halfSize.cy = height >> 1;
}

void Renderer::Draw(HDC hdc)
{
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hBitmap);

	// 게임 오브젝트 위치를 중심으로 비트맵을 복사
	const Vector2& pos = gameObject.GetPosition();
	const Vector2& ratio = Application::GetRatio();
	StretchBlt(hdc, (pos.x - halfSize.cx) * ratio.x, (pos.y - halfSize.cy) * ratio.y, size.cx * ratio.x, size.cy * ratio.y, memDC, 1, 0, bmSize.cx - 2, bmSize.cy, SRCCOPY);

	DeleteDC(memDC);
}

Renderer::Renderer(int bmId, GameObject& gameObject)
	:Component(gameObject)
{
	renderers.push_back(this);

	hBitmap = LoadBitmap(Application::GetInstanceHandle(), MAKEINTRESOURCE(bmId));
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm);

	bmSize.cx = bm.bmWidth;
	bmSize.cy = bm.bmHeight;

	SetSize(bmSize.cx, bmSize.cy);
}

Renderer::~Renderer()
{
	auto iter = find(renderers.begin(), renderers.end(), this);
	if (iter != renderers.end())// 찾았다면
	{
		// 해당 요소를 동적배열에서 제거
		renderers.erase(iter);
	}
}
