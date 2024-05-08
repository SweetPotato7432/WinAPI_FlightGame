#include "Bullet.h"
#include "Time.h"
#include "AtlasRenderer.h"
#include "resource.h"
#include "Animation.h"

void Bullet::Update()
{
	Move(dir * moveSpeed * Time::GetDeltaTime());
}

Bullet::Bullet(queue<Bullet*>& bulletPool)
	: dir({ 1.0f,0.0f }), moveSpeed(1000.0f), bulletPool(bulletPool)
{
	renderer = new AtlasRenderer(IDB_BULLET, *this, 5, RGB(255, 255, 255));
	renderer->SetSize(30, 40);

	int arr[] = { 0,1,2,3,4 };
	Animation* animation = new Animation(*this, *renderer, arr, 5, true, 0.05f);
}
