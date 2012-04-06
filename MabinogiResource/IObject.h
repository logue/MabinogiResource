#pragma once

#include "ExportMacro.h"

class MABINOGIRESOURCE_API IObject
{
public:

	IObject(void)
	{
	}

	virtual ~IObject(void)
	{
	}

	// 进行释放操作
	virtual void Release() = 0;

private:
	IObject(IObject const & other);
	IObject& operator=(IObject const & other);
};

