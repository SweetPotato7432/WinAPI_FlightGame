#include "Input.h"

map<int, bool> Input::keyMap;

void Input::SetKey(int keyCode, bool value)
{
	// map<T1, T2>.find([key])
	// [key]에 해당하는 요소의 iterator를 찾는 메서드
	// 반환 데이터
	//  : 요소를 찾을 경우, 해당 요소의 iterator 반환
	//	요소를 찾지 못할 경우 end()반환

	if (keyMap.find(keyCode) == keyMap.end()) //keyCode에 해당하는 요소를 못찾았다면
	{
		keyMap.insert({ keyCode,value }); // 요소를 추가한다.
	}
	else //찾았다면
	{
		keyMap[keyCode] = value;//요소의 값을 변경
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
