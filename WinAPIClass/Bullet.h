#pragma once
#include "GameObject.h"
#include <queue>
using namespace std;

class AtlasRenderer;

class Bullet : public GameObject
{
	
private :
	queue<Bullet*>& bulletPool;
	AtlasRenderer* renderer;

private : 
	Vector2 dir; // �Ѿ��� ���ư��� ����
	float moveSpeed;//�Ѿ��� ���ư��� �ӵ�

public :
	virtual void Update();

public:
	Bullet(queue<Bullet*>& bulletPool);
	~Bullet() = default;

};

