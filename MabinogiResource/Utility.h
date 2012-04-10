#pragma once

#include "IResource.h"
#include <memory>
#include <vector>

using namespace std;
using namespace std::tr1;

class ResourceGreater
{
public:
	bool operator()(shared_ptr<IResource> spResource1, shared_ptr<IResource> spResource2) 
	{
		return spResource1->GetName() > spResource2->GetName();
	}
};

class CUtility
{
public:
	CUtility(void);
	~CUtility(void);

	// 二分查找已排序资源，找不到返回-1
	static int BinaryFindResourceIndex(vector<shared_ptr<IResource>> & resList, LPCTSTR lpszName);

	// 顺序查找资源，找不到返回-1
	static int FindResourceIndex(vector<shared_ptr<IResource>> & resList, LPCTSTR lpszName);

	// 加密一段字节
	static void Encrypt(char * pBuffer, size_t size, size_t seed);
	
	// 解密一段字节
	static void Decrypt(char * pBuffer, size_t size, size_t seed);

	static bool ZlibUncompress (void * dest, unsigned long * destLen,
		const void * source, unsigned long sourceLen);

	static bool ZlibCompress (void * dest, unsigned long * destLen,
		const void * source, unsigned long sourceLen, int level);
};
