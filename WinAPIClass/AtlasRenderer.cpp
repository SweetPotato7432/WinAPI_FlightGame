#include "AtlasRenderer.h"
#include "GameObject.h"
#include "Application.h"
#pragma comment(lib, "msimg32.lib")

void AtlasRenderer::Draw(HDC hdc)
{
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hBitmap);

	// ���� ������Ʈ ��ġ�� �߽����� ��Ʈ���� ����
	const Vector2& pos = gameObject.GetPosition();
	const Vector2& ratio = Application::GetRatio();
	StretchBlt(hdc, (pos.x - halfSize.cx) * ratio.x,
		(pos.y - halfSize.cy) * ratio.y,
		size.cx * ratio.x,
		size.cy * ratio.y,
		memDC, widthPerImage * index, 0, widthPerImage, bmSize.cy, SRCCOPY);

	DeleteDC(memDC);
}

void AtlasRenderer::SetIndex(int index)
{
	if (index >= 0 && index < count) {
		this->index = index;
	}
}

AtlasRenderer::AtlasRenderer(int bmId, GameObject& gameObject, int count, COLORREF removeColor)
	:Renderer(bmId, gameObject), count(count), backgroundColor(removeColor), index(0)
{
	widthPerImage = bmSize.cx / count;
}
