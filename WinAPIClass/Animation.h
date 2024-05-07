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
	float time; // ���� �̹����� �ѱ�� ���� �ɸ��� �ð�
	float timeCheck; // �ð� ������

private:
	bool loop; // �ִϸ��̼� �ݺ� ����

private:
	void Update();

public:
	void Initialize(); // �̹��� �ʱ�ȭ 

public:
	Animation(GameObject& gameObject, AtlasRenderer& atlasRenderer, int* indexArr, int maxCount, bool loop, float sec);
	~Animation();
};

