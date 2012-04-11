#pragma once

#include "ExportMacro.h"

class MABINOGIRESOURCE_API IObject
{
public:
	// Constructor
	IObject(void){}

	// Destructor
	virtual ~IObject(void){}

	// The release operation
	virtual void Release() = 0;

private:
	IObject(IObject const & other);
	IObject& operator=(IObject const & other);
};

