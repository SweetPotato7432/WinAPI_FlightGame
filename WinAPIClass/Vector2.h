#pragma once

// 실수형 좌표 구조체
typedef struct tagVector2
{
public:
	float x;
	float y;

public:
	tagVector2 operator+(const tagVector2& v);
	tagVector2 operator-(const tagVector2& v);
	tagVector2 operator*(const float f);

	tagVector2& operator+=(const tagVector2& v);
	tagVector2& operator-=(const tagVector2& v);
	tagVector2& operator*=(const float f);

public:
	tagVector2();
	tagVector2(float x, float y);
	~tagVector2() = default;

}Vector2;