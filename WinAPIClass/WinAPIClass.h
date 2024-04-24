#pragma once

#include "resource.h"
#include "GraphicManager.h"

#include <string>
using namespace std;

// TCHAR 버전 string 자료구조
#ifdef UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif