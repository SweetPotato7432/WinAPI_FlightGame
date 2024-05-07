#pragma once
#include <map>
using namespace std;

class Input
{
private:
	static map<int, bool> keyMap;

public:
	static void SetKey(int keyCode, bool value);
	static bool GetKey(int keyCode);
};


