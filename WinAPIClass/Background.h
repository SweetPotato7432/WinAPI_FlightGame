#pragma once
#include "GameObject.h"

class Renderer;

class Background : public GameObject
{
private:
	Renderer* renderer;

public:
	Background();
	~Background() = default;
};

