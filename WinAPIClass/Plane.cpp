#include "Plane.h"
#include "AtlasRenderer.h"
#include "Animation.h"
#include "resource.h"
#include "Input.h"
#include "Time.h"
#include "Bullet.h"


// �ִϸ��̼��� �ߺ� ����Ǵ°��� �����ϱ� ���� �޼���
void Plane::SetState(State state)
{
	if (this->state != state)
	{
		this->state = state;
		for (int i = 0; i < MAXCOUNT; i++)
		{
			// i�� state�� ���ٸ� animationArr[i] Ȱ��ȭ
			// i�� state�� �ٸ��ٸ� animationArr[i] ��Ȱ��ȭ
			animationArr[i]->SetActive(i == state);

			// ���¿� �´� �̹����� �ʱ�ȭ
			if (i == state) {
				animationArr[i]->Initialize();
			}
		}
		
	}
}
void Plane::CreateBullets()
{
	// Bullet ��ü�� ���� �� ��Ȱ��ȭ
	// bulletPool�� �ּҸ� ����
	// 20 �� �ݺ�
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
	// empty : ����ִ�
	// �ش� queue<T>�� ��������� true, ������� ������ false
	// bulletPool ť�� ����ִٸ� �Ѿ��� �����ض�
	// �Ѿ��� ��� �����ϸ� �޸𸮰� ������ ���ɼ��� �����Ѵ�.
	if (bulletPool.empty())
		CreateBullets();

	// ��Ÿ���� �����߸� �߻簡 �ȴ�.
	if (shootTimeCheck >= shootCoolTime) {
		shootTimeCheck = 0.0f;
		Bullet* bullet = bulletPool.front();
		bullet->SetPosition(position);
		bullet->SetActive(true);

		// queue<T>.pop() : ��ȯ������ ����, �����⸸ ��
		bulletPool.pop();
	}



}
void Plane::Update()
{
	// ����� �̵�
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
