#pragma once
#include "framework.h"

//델타 타임을 관리하는 클래스
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

