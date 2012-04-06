#pragma once

#include "IResourceSet.h"

#include <memory>
#include <vector>

using namespace std;
using namespace std::tr1;

class CResourceFileSystem : public IResourceSet
{
public:
	CResourceFileSystem(void);

	virtual ~CResourceFileSystem(void);

	// 从一个pack文件夹创建
	bool Open(LPCTSTR lpszPackFolder);

	// 找到指定全名的资源
	virtual int FindResourceIndex(LPCTSTR lpszName);

	// 获得一个资源
	virtual IResource * GetResource(size_t index);

	// 获得资源总数
	virtual size_t GetResourceCount();

	virtual void Release();
protected:
	vector<shared_ptr<IResource>> m_Resources;
};
