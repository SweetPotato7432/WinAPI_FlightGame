#pragma once
#include "GameObject.h"
#include <queue>
using namespace std;

class Animation;
class Bullet;

class Plane : public GameObject
{
private:
	//enum: 정수에 별명을 붙여 사용
	enum State
	{
		// NONE이 있는 이유 : State를 변경할때 다른 State를 비활성화 시키기 위해서
		NONE = -1,
		IDLE, // 기본
		ATTACK, // 공격
		DEAD, // 파괴
		MAXCOUNT
	};

private:
	Animation* animationArr[MAXCOUNT];
	State state; // 현재 상태

private:
	queue<Bullet*> bulletPool;
	int bulletCount;

	// 총알 발사 쿨타임을 정하기 위하여
	const float shootCoolTime;
	float shootTimeCheck;

private:
	void SetState(State state);
	void CreateBullets();//총알 생성
	void Shoot();// 총알 발사

public:
	virtual void Update();

public:
	Plane();
	~Plane() = default;
};

