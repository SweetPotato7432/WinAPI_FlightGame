#include "Time.h"

// deltaTiem�� ����ϴ� ����
// (���� ��)�� ���� �ð��� �����Ͽ� ����ð����� ���� �ð��� ���� ����Ѵ�.
// ���� �ð��� �ƴ� 
// 
// LARGE_INTEGER
//   union : ����ü

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
