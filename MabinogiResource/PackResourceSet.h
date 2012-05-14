#pragma once
#include "iresourceset.h"

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::tr1;

class CPackResourceSet : public IResourceSet
{
public:
	friend class CResourceFileSystem;

	CPackResourceSet();

	virtual ~CPackResourceSet(void);

	bool Open(LPCTSTR lpszPackFile);


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

static char* ConvertToANSI(const wchar_t* szUnicode);
static wchar_t* ConvertToWide(const char* text);