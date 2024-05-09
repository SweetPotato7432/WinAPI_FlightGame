#include "Bullet.h"
#include "Time.h"
#include "AtlasRenderer.h"
#include "resource.h"
#include "Animation.h"

void Bullet::Update()
{
	// 지속 시간이 지난 총알을 비활성화 시키고 다시 큐에 넣는다.
	// Plane 클래스에서 Shoot()을 실행하면 다시 발사 가능하다.
	if (lifeTimeCheck >= lifeTime)
	{
		lifeTimeCheck = 0.0f;
		bulletPool.push(this);
		SetActive(false);
	}
	else
	{
		lifeTimeCheck += Time::GetDeltaTime();
	}
	Move(dir * moveSpeed * Time::GetDeltaTime());
}

Bullet::Bullet(queue<Bullet*>& bulletPool)
	: dir({ 1.0f,0.0f }), moveSpeed(1000.0f), bulletPool(bulletPool), lifeTime(2.0f), lifeTimeCheck(0.0f)
{
	renderer = new AtlasRenderer(IDB_BULLET, *this, 5, RGB(255, 255, 255));
	renderer->SetSize(30, 40);

	int arr[] = { 0,1,2,3,4 };
	Animation* animation = new Animation(*this, *renderer, arr, 5, true, 0.05f);
}
