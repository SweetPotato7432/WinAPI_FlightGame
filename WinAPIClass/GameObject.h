#pragma once
#include "framework.h"
#include "Vector2.h"
#include <vector>
using namespace std;

// <���� ������Ʈ>
// - ��ġ
//	Vector2 ����ü ���
// - Ȱ��ȭ ����
// - �̵�()
// - Ȱ��ȭ ���()
// -'���� ���' ���
//	- �̹��� ���� ���
//		- Ȱ��ȭ ����
//		- �̹���
//		- �׸���()
//  ��..
//

class GameObject
{
private:
	// vector : ���� �迭 �ڷ� ����
	// static : ���α׷��� ���� �� �� ����, ���� �� �� ����
	static vector<GameObject*> gameObjects;

public:
	static void EventUpdate();

private:
	Vector2 position; // ��ġ
	bool active; // Ȱ��ȭ ����

public:
	void Move(const Vector2& v); // �̵�()
	void SetActive(bool value); // Ȱ��ȭ ���()

public:
	virtual void Update();

public:
	GameObject();
	virtual ~GameObject();
};

