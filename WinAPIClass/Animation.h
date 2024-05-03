#pragma once
#include "Component.h"
#include <vector>
using namespace std;

class AtlasRenderer;

class Animation : public Component
{
private:
	static vector<Animation*> animations;

public:
	static void EventUpdate();

private:
	AtlasRenderer& atlasRenderer;

private:
	int* indexArr; // 이미지 번호 목록
	int index; // 현재 이미지 순서
	int count; // 총 이미지 번호 개수

private:
	bool loop; // 애니메이션 반복 설정

private:
	void Update();

public:
	Animation(GameObject& gameObject, AtlasRenderer& atlasRenderer, int* indexArr, int maxCount, bool loop);
	~Animation();
};

