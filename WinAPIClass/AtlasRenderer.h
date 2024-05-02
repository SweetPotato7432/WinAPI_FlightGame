#pragma once
#include "Renderer.h"

//Atlas : ���� ���� �̹����� �ϳ��� ������ �̹���
class AtlasRenderer : public Renderer
{
	// ��ĭ �� �ʺ� ���ϱ� ���� ���� �̹��� �ʺ�� �̹��� ������ �ʿ��ϴ�.
private:
	int index; // �̹��� ��ȣ
	int count; // �̹��� ����
	int widthPerImage; // �̹��� �� ĭ �� �ʺ�

private:
	COLORREF backgroundColor; // ��� ��(������ ��� ��)

public:
	virtual void Draw(HDC hdc);
	void SetIndex(int index);

public:
	AtlasRenderer(int bmId, GameObject& gameObject, int count, COLORREF removeColor);
	~AtlasRenderer() = default;
};

