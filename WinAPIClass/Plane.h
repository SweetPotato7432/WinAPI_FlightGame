#pragma once
#include "GameObject.h"

class Animation;

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
	void SetState(State state);

public:
	Plane();
	~Plane() = default;
};

