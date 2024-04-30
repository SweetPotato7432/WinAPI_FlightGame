#include "Time.h"

// deltaTiem을 계산하는 원리
// (진동 수)빈도 마다 시간을 측정하여 현재시간에서 이전 시간을 빼서 계산한다.
// 실제 시간이 아님 
// 
// LARGE_INTEGER
//   union : 공용체

double Time::deltaTime = 0.0;
double Time::freq = 0.0;
LARGE_INTEGER Time::currentTime;
LARGE_INTEGER Time::lastTime;

float Time::GetDeltaTime()
{
    return (float)deltaTime;
}

void Time::Start()
{
    LARGE_INTEGER freqPerSec;
    QueryPerformanceFrequency(&freqPerSec);
    QueryPerformanceCounter(&lastTime);

    currentTime = lastTime;
    freq = 1.0 / (double)freqPerSec.QuadPart;
}

void Time::Update()
{
    QueryPerformanceCounter(&currentTime);

    deltaTime = (currentTime.QuadPart - lastTime.QuadPart) * freq;
    lastTime = currentTime;
}
