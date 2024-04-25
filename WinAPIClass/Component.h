#pragma once

class GameObject; // GameObject��� Ŭ������ �����Ѵ�. ��� ����

//Component : ���� ���
//GameObject�� �߰����� ����� ����ϴ� ���
class Component
{
protected:
	// ������Ʈ�� ������ ���ӿ�����Ʈ ��ü
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

