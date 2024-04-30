#pragma once
#include "framework.h"
#include "Vector2.h"
#include <vector>
using namespace std;

class Component; // Component��� Ŭ������ �����Ѵ�. ��� ����

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
	static void EventQuit();

protected:
	Vector2 position; // ��ġ
	bool active; // Ȱ��ȭ ����

private:
	// ComponentŬ���� ��ü�� �ּҸ� ����
	vector<Component*> componentList;

public:
	void Move(const Vector2& v); // �̵�()
	void SetActive(bool value); // Ȱ��ȭ ���()	
	void SetPosition(const Vector2& pos);
	const Vector2& GetPosition();



public:
	// ������Ʈ�� �߰��ϴ� �Լ�
	void AddComponent(Component* component);

public:
	virtual void Update();

public:
	GameObject();
	virtual ~GameObject();
};

