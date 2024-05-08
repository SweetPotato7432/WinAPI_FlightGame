#pragma once
#include "GameObject.h"
#include <queue>
using namespace std;

class Animation;
class Bullet;

class Plane : public GameObject
{
private:
	//enum: ������ ������ �ٿ� ���
	enum State
	{
		// NONE�� �ִ� ���� : State�� �����Ҷ� �ٸ� State�� ��Ȱ��ȭ ��Ű�� ���ؼ�
		NONE = -1,
		IDLE, // �⺻
		ATTACK, // ����
		DEAD, // �ı�
		MAXCOUNT
	};

private:
	Animation* animationArr[MAXCOUNT];
	State state; // ���� ����

private:
	queue<Bullet*> bulletPool;
	int bulletCount;

	// �Ѿ� �߻� ��Ÿ���� ���ϱ� ���Ͽ�
	const float shootCoolTime;
	float shootTimeCheck;

private:
	void SetState(State state);
	void CreateBullets();//�Ѿ� ����
	void Shoot();// �Ѿ� �߻�

public:
	virtual void Update();

public:
	Plane();
	~Plane() = default;
};

