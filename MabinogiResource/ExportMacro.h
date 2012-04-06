#pragma once

#ifdef MABINOGIRESOURCE_EXPORTS
#define MABINOGIRESOURCE_API __declspec(dllexport)
#else
#define MABINOGIRESOURCE_API __declspec(dllimport)
#endif