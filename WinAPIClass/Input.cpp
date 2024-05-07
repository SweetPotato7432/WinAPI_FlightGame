#include "Input.h"

map<int, bool> Input::keyMap;

void Input::SetKey(int keyCode, bool value)
{
	// map<T1, T2>.find([key])
	// [key]�� �ش��ϴ� ����� iterator�� ã�� �޼���
	// ��ȯ ������
	//  : ��Ҹ� ã�� ���, �ش� ����� iterator ��ȯ
	//	��Ҹ� ã�� ���� ��� end()��ȯ

	if (keyMap.find(keyCode) == keyMap.end()) //keyCode�� �ش��ϴ� ��Ҹ� ��ã�Ҵٸ�
	{
		keyMap.insert({ keyCode,value }); // ��Ҹ� �߰��Ѵ�.
	}
	else //ã�Ҵٸ�
	{
		keyMap[keyCode] = value;//����� ���� ����
	}
}

bool Input::GetKey(int keyCode)
{
	if (keyMap.find(keyCode) == keyMap.end())
	{
		keyMap.insert({ keyCode, false });
	}
	return keyMap[keyCode];
}
