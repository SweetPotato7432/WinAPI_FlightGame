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
	virtual void Update(); // �޼��� ������

public:
	Background();
	~Background() = default;
};

