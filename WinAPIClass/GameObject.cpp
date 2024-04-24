#include "GameObject.h"

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

void GameObject::Move(const Vector2& v)
{
	position += v;
}

void GameObject::SetActive(bool value)
{
	if (active != value) {
		active = value;
	}
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

}
