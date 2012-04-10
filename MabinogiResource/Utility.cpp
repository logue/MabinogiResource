#include "StdAfx.h"
#include "Utility.h"

#include "MersenneTwister.h"

#include "zlib-1.2.6/zlib.h"
//#pragma comment(lib, "zlib125-dll/lib/zdll.lib")

CUtility::CUtility(void)
{
}

CUtility::~CUtility(void)
{
}

int CUtility::FindResourceIndex( vector<shared_ptr<IResource>> & resList, LPCTSTR lpszName )
{
	for (size_t i = 0;i < resList.size();i++)
	{
		if (lstrcmpi(resList.at(i)->GetName(), lpszName) == 0)
		{
			return i;
		}
	}

	return -1;
}

int CUtility::BinaryFindResourceIndex( vector<shared_ptr<IResource>> & resList, LPCTSTR lpszName )
{
	size_t begin = 0, end = resList.size() - 1;
	while (begin <= end)
	{
		int middle = (end - begin) / 2 + begin;
		shared_ptr<IResource> spResrouce = resList.at(middle);
		int result = lstrcmpi(spResrouce->GetName(), lpszName);

		if (result == 0)
		{
			return middle;
		}
		else if (result > 0)
		{
			begin = middle + 1;
		}
		else
		{
			end = middle - 1;
		}

	}

	return -1;
}

void CUtility::Encrypt(char * pBuffer, size_t size, size_t seed )
{
	// 加密
	CMersenneTwister mt;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	mt.init_genrand(rseed);
	for (size_t i = 0; i < size;i++)
	{
		pBuffer[i] = (char)(pBuffer[i]  ^ mt.genrand_int32());
	}
}

void CUtility::Decrypt(char * pBuffer, size_t size, size_t seed )
{
	CMersenneTwister mt;
	unsigned long rseed = (seed << 7) ^ 0xA9C36DE1;
	mt.init_genrand(rseed);
	for (size_t i = 0; i < size;i++)
	{
		pBuffer[i] = (char)(pBuffer[i]  ^ mt.genrand_int32());
	}
}

bool CUtility::ZlibUncompress( void * dest, unsigned long * destLen, const void * source, unsigned long sourceLen )
{
	return uncompress((Bytef *)dest, destLen, (Bytef *)source, sourceLen) == Z_OK;
}

bool CUtility::ZlibCompress( void * dest, unsigned long * destLen, const void * source, unsigned long sourceLen, int level=Z_DEFAULT_COMPRESSION)
{
	return compress2((Bytef *)dest, destLen, (Bytef *)source, sourceLen, level) == Z_OK;
}
