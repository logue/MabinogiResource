#pragma once

#ifdef _WINDLL
#define MABINOGIRESOURCE_API __declspec(dllexport)
#else
#define MABINOGIRESOURCE_API __declspec(dllimport)
#endif