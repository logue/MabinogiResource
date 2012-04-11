#pragma once

#include "ExportMacro.h"
#include "IResource.h"
#include "IProgressMonitor.h"

class MABINOGIRESOURCE_API IResourceSet : public IObject
{
public:
	// Constructor
	IResourceSet(void){}
	
	// Destructor
	virtual ~IResourceSet(void){}

	// Find to specify the full name of the resource
	virtual int FindResourceIndex(LPCTSTR lpszName) = 0;

	// Access to a resource
	virtual IResource * GetResource(size_t index) = 0;

	// Total number of resources
	virtual size_t GetResourceCount() = 0;

	static bool PackResources( IResource ** resources, size_t size, size_t version, LPCTSTR lpszPackFile, IProgressMonitor * pMonitor, int level);

	static IResourceSet * CreateResourceSetFromFolder(LPCTSTR lpszPackFolder);

	static IResourceSet * CreateResourceSetFromFile(LPCTSTR lpszFile);
}; 
