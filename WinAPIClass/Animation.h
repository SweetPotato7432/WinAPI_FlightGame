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
	int* indexArr; // �̹��� ��ȣ ���
	int index; // ���� �̹��� ����
	int count; // �� �̹��� ��ȣ ����

private:
	bool loop; // �ִϸ��̼� �ݺ� ����

private:
	void Update();

public:
	Animation(GameObject& gameObject, AtlasRenderer& atlasRenderer, int* indexArr, int maxCount, bool loop);
	~Animation();
};

