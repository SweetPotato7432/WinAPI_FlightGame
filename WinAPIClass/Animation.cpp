#include "Animation.h"
#include "AtlasRenderer.h"

vector<Animation*> Animation::animations;

void Animation::EventUpdate()
{
	int length = animations.size();
	for (int i = 0; i < length; i++)
	{
		Animation& temp = *animations[i];
		if (temp.active)
		{
			temp.Update();
		}
	}
}

// ���� �̹����� �ѱ�� ��Ȱ
void Animation::Update()
{
	if (index < count - 1)
	{
		index++;
	}
	else
	{
		if (loop)
		{
			index = 0;
		}
	}
	atlasRenderer.SetIndex(indexArr[index]);
}

Animation::Animation(GameObject& gameObject, AtlasRenderer& atlasRenderer, int* indexArr, int maxCount, bool loop)
	:Component(gameObject), atlasRenderer(atlasRenderer), count(maxCount), loop(loop)
{
	animations.push_back(this);

	this->indexArr = new int[maxCount]; // ���� �迭 ���� �迭
	//memcpy_s() : �޸� ���� �Լ�
	memcpy_s(this->indexArr, sizeof(int) * maxCount, indexArr, sizeof(int) * maxCount);
}

Animation::~Animation()
{
	auto iter = find(animations.begin(), animations.end(), this);
	if (iter != animations.end()) {
		animations.erase(iter);
	}
	if (indexArr != nullptr) {
		delete[] indexArr;
		indexArr = nullptr;
	}
}
