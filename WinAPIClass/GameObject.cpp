#include "GameObject.h"
#include "Component.h"

vector<GameObject*> GameObject::gameObjects;

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

void GameObject::EventQuit()
{
	int length = gameObjects.size();
	for (int i = 0; i < length; i++) {
		// 게임 오브젝트를 해제
		delete gameObjects[i];
	}
	// 게임 오브젝트 배열 초기화
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
		// GameObject를 활성화/비활성화 할때 Component도 활성화/비활성화
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
	// TODO: 여기에 return 문을 삽입합니다.
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
