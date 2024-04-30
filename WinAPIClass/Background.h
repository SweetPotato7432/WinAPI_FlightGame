#pragma once
#include "GameObject.h"

class Renderer;

class Background : public GameObject
{
private:
	Renderer* renderer;

private:
	float scrollSpeed;

public:
	virtual void Update(); // 메서드 재정의

public:
	Background();
	~Background() = default;
};

