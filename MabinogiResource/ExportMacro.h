#pragma once

#define WIN32_LEAN_AND_MEAN 
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

#ifndef MABINOGIRESOURCE_API
#define MABINOGIRESOURCE_API __declspec(dllexport)
#endif
