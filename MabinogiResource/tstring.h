#pragma once
#include <string>

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif