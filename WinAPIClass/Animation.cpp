#include "Animation.h"
#include "AtlasRenderer.h"
#include "Time.h"

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

// 다음 이미지로 넘기는 역활
void Animation::Update()
{
	//timeCheck에 DeltaTime을 계속 더한다.
	timeCheck += Time::GetDeltaTime();
	//그러다가 timeCheck가 time을 넘었다면 실행
	if (timeCheck >= time)
	{
		// timeCheck는 다시 계산을 위해 time을 빼준다.
		timeCheck -= time;
		//실행할 코드
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
}

void Animation::Initialize()
{
	//이미지 순서를 0으로 만들고 애니메이션의 1번째 이미지를 띄운다.
	index = 0;
	timeCheck = 0.0f;
	atlasRenderer.SetIndex(indexArr[index]);
}

Animation::Animation(GameObject& gameObject, AtlasRenderer& atlasRenderer, int* indexArr, int maxCount, bool loop, float sec)
	:Component(gameObject), atlasRenderer(atlasRenderer), count(maxCount), loop(loop), time(sec), timeCheck(0.0f)
{
	animations.push_back(this);

	this->indexArr = new int[maxCount]; // 정수 배열 동적 배열
	//memcpy_s() : 메모리 복사 함수
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
