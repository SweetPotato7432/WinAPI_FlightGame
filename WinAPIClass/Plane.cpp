#include "Plane.h"
#include "AtlasRenderer.h"
#include "Animation.h"
#include "resource.h"
#include "Input.h"
#include "Time.h"


// 애니메이션이 중복 실행되는것을 방지하기 위한 메서드
void Plane::SetState(State state)
{
	if (this->state != state)
	{
		this->state = state;
		for (int i = 0; i < MAXCOUNT; i++)
		{
			// i가 state와 같다면 animationArr[i] 활성화
			// i가 state와 다르다면 animationArr[i] 비활성화
			animationArr[i]->SetActive(i == state);
		}
	}
}

void Plane::Update()
{
	// 비행기 이동
	Vector2 dir;
	if (Input::GetKey(VK_LEFT)) {
		dir.x -= 1.0f;
	}
	if (Input::GetKey(VK_RIGHT)) {
		dir.x += 1.0f;
	}
	if (Input::GetKey(VK_UP)) {
		dir.y -= 1.0f;
	}
	if (Input::GetKey(VK_DOWN)) {
		dir.y += 1.0f;
	}
	Move(dir * 400.0f * Time::GetDeltaTime());

}

Plane::Plane() : state(NONE)
{
	AtlasRenderer* renderer = new AtlasRenderer(IDB_PLANE, *this, 8, RGB(255, 0, 255));

	renderer->SetSize(200, 150);

	int arr[8] = { 0,1,2,3,4,5,6,7 };
	animationArr[IDLE] = new Animation(*this, *renderer, arr + 1, 2, true,0.1f);
	animationArr[ATTACK] = new Animation(*this, *renderer, arr + 3, 5, true,0.1f);
	animationArr[DEAD] = new Animation(*this, *renderer, arr, 1, false,0.1f);

	SetState(IDLE);
}
