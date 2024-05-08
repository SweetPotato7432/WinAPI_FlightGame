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
	Vector2 dir; // 총알이 날아가는 방향
	float moveSpeed;//총알이 날아가는 속도

public :
	virtual void Update();

public:
	Bullet(queue<Bullet*>& bulletPool);
	~Bullet() = default;

};

