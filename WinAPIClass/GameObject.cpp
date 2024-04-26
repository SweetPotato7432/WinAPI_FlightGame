#include "GameObject.h"
#include "Component.h"

vector<GameObject*> GameObject::gameObjects;

void GameObject::EventUpdate()
{
	int length = gameObjects.size();
	for (int i = 0; i < length; i++) {
		GameObject& temp = *gameObjects[i];
		if (temp.active) //���� gameObject�� Ȱ��ȭ �Ǿ� �ִٸ�
		{
			temp.Update(); // Update()�� �����Ѵ�.
		}
	}
}

void GameObject::EventQuit()
{
	int length = gameObjects.size();
	for (int i = 0; i < length; i++) {
		// ���� ������Ʈ�� ����
		delete gameObjects[i];
	}
	// ���� ������Ʈ �迭 �ʱ�ȭ
	gameObjects.clear();
}

void GameObject::Move(const Vector2& v)
{
	position += v;
}

void GameObject::SetActive(bool value)
{
	if (active != value) {
		active = value;
		int length = componentList.size();
		// GameObject�� Ȱ��ȭ/��Ȱ��ȭ �Ҷ� Component�� Ȱ��ȭ/��Ȱ��ȭ
		for (int i = 0; i < length; i++) {
			componentList[i]->SetActive(active);
		}
	}
}

void GameObject::SetPosition(const Vector2& pos)
{
	position = pos;
}

const Vector2& GameObject::GetPosition()
{
	// TODO: ���⿡ return ���� �����մϴ�.
	return position;
}

void GameObject::AddComponent(Component* component)
{
	componentList.push_back(component);
}

void GameObject::Update()
{
}


GameObject::GameObject() : active(true)
{
	gameObjects.push_back(this);
}

GameObject::~GameObject()
{
	int length = componentList.size();
	for (int i = 0; i < length; i++) {
		delete componentList[i];
	}
	componentList.clear();
}
