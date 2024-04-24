#include "GameObject.h"

void GameObject::EventUpdate()
{
	int length = gameObjects.size();
	for (int i = 0; i < length; i++) {
		GameObject& temp = *gameObjects[i];
		if (temp.active) //현재 gameObject가 활성화 되어 있다면
		{
			temp.Update(); // Update()를 실행한다.
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
