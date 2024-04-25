#pragma once

class GameObject; // GameObject라는 클래스가 존재한다. 라고만 선언

//Component : 구성 요소
//GameObject의 추가적인 기능을 담당하는 요소
class Component
{
protected:
	// 컴포넌트를 장착할 게임오브젝트 객체
	GameObject& gameObject;

protected:
	bool active;

public:
	void SetActive(bool value);
	bool IsActive();


public:
	Component(GameObject& gameObject);
	virtual ~Component() = default;

};

