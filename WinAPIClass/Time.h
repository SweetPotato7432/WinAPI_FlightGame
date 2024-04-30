#pragma once
#include "framework.h"

//��Ÿ Ÿ���� �����ϴ� Ŭ����
class Time
{
private:
	static double deltaTime;

private:
	static LARGE_INTEGER lastTime;
	static LARGE_INTEGER currentTime;
	static double freq;

public:
	static float GetDeltaTime();

public:
	static void Start();
	static void Update();
};

