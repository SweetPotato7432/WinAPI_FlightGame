#pragma once
#include "Renderer.h"

//Atlas : 여러 장의 이미지가 하나로 합쳐진 이미지
class AtlasRenderer : public Renderer
{
	// 한칸 당 너비를 구하기 위해 기존 이미지 너비와 이미지 개수가 필요하다.
private:
	int index; // 이미지 번호
	int count; // 이미지 개수
	int widthPerImage; // 이미지 한 칸 당 너비

private:
	COLORREF backgroundColor; // 배경 색(제거할 배경 색)

public:
	virtual void Draw(HDC hdc);
	void SetIndex(int index);

public:
	AtlasRenderer(int bmId, GameObject& gameObject, int count, COLORREF removeColor);
	~AtlasRenderer() = default;
};

