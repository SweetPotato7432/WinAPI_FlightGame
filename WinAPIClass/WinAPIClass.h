#pragma once

#include "resource.h"
#include "GraphicManager.h"

#include <string>
using namespace std;

// TCHAR ���� string �ڷᱸ��
#ifdef UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif