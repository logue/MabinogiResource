#pragma once

#include "ExportMacro.h"
#include "IResource.h"
#include "IProgressMonitor.h"

class MABINOGIRESOURCE_API IResourceSet : public IObject
{
public:

	IResourceSet(void){}

	virtual ~IResourceSet(void){}

	// 找到指定全名的资源
	virtual int FindResourceIndex(LPCTSTR lpszName) = 0;

	// 获得一个资源
	virtual IResource * GetResource(size_t index) = 0;

	// 获得资源总数
	virtual size_t GetResourceCount() = 0;

	static bool PackResources( IResource ** resources, size_t size, size_t version, LPCTSTR lpszPackFile, IProgressMonitor * pMonitor);

	static IResourceSet * CreateResourceSetFromFolder(LPCTSTR lpszPackFolder);

	static IResourceSet * CreateResourceSetFromFile(LPCTSTR lpszFile);
}; 
