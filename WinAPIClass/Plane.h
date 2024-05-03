#pragma once
#include "GameObject.h"

class Animation;

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
	void SetState(State state);

public:
	Plane();
	~Plane() = default;
};

