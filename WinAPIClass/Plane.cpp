#include "Plane.h"
#include "AtlasRenderer.h"
#include "Animation.h"
#include "resource.h"
#include "Input.h"
#include "Time.h"
#include "Bullet.h"


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

			// 상태에 맞는 이미지를 초기화
			if (i == state) {
				animationArr[i]->Initialize();
			}
		}
		
	}
}
void Plane::CreateBullets()
{
	// Bullet 객체를 생성 후 비활성화
	// bulletPool에 주소를 저장
	// 20 번 반복
	for (int i = 0; i < bulletCount; i++)
	{
		Bullet* bullet = new Bullet(bulletPool);
		bullet->SetActive(false);
		bulletPool.push(bullet);
	}
}

void Plane::Shoot()
{
	// queue<T>.empty()
	// empty : 비어있는
	// 해당 queue<T>가 비어있으면 true, 비어있지 않으면 false
	// bulletPool 큐가 비어있다면 총알을 생성해라
	// 총알을 계속 생성하면 메모리가 부족할 가능성이 존재한다.
	if (bulletPool.empty())
		CreateBullets();

	// 쿨타임을 지나야만 발사가 된다.
	if (shootTimeCheck >= shootCoolTime) {
		shootTimeCheck = 0.0f;
		Bullet* bullet = bulletPool.front();
		bullet->SetPosition(position);
		bullet->SetActive(true);

		// queue<T>.pop() : 반환데이터 없음, 꺼내기만 함
		bulletPool.pop();
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
	if (Input::GetKey(VK_SPACE)) {
		Shoot();
	}
	if (shootTimeCheck < shootCoolTime) {
		shootTimeCheck += Time::GetDeltaTime();
	}
	Move(dir * 400.0f * Time::GetDeltaTime());

}

Plane::Plane() : state(NONE), bulletCount(20), shootCoolTime(0.1f), shootTimeCheck(shootCoolTime)
{
	AtlasRenderer* renderer = new AtlasRenderer(IDB_PLANE, *this, 8, RGB(255, 0, 255));

	renderer->SetSize(200, 150);

	int arr[8] = { 0,1,2,3,4,5,6,7 };
	animationArr[IDLE] = new Animation(*this, *renderer, arr + 1, 2, true,0.1f);
	animationArr[ATTACK] = new Animation(*this, *renderer, arr + 3, 5, true,0.1f);
	animationArr[DEAD] = new Animation(*this, *renderer, arr, 1, false,0.1f);

	SetState(IDLE);
	CreateBullets();
}
