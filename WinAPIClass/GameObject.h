#pragma once
#include "framework.h"
#include "Vector2.h"
#include <vector>
using namespace std;

// <게임 오브젝트>
// - 위치
//	Vector2 구조체 사용
// - 활성화 상태
// - 이동()
// - 활성화 기능()
// -'구성 요소' 목록
//	- 이미지 구성 요소
//		- 활성화 상태
//		- 이미지
//		- 그리기()
//  등..
//

class GameObject
{
private:
	// vector : 동적 배열 자료 구조
	// static : 프로그램이 실행 될 때 생성, 종료 될 때 해제
	static vector<GameObject*> gameObjects;

public:
	static void EventUpdate();

private:
	Vector2 position; // 위치
	bool active; // 활성화 상태

public:
	void Move(const Vector2& v); // 이동()
	void SetActive(bool value); // 활성화 기능()

public:
	virtual void Update();

public:
	GameObject();
	virtual ~GameObject();
};

