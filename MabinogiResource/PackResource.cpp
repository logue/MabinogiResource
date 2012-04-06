#include "StdAfx.h"
#include "PackResource.h"

#include "Utility.h"
#include "Win32File.h"


CPackResource::CPackResource( tstring name, shared_ptr<CWin32File> spFile, ITEM_INFO * pInfo )
{
	m_name = name;
	m_spFile = spFile;
	m_info = *pInfo;
}

CPackResource::~CPackResource(void)
{
}

LPCTSTR CPackResource::GetName() 
{
	return m_name.c_str();
}

size_t CPackResource::GetCompressedSize() 
{
	return m_info.compress_size;
}

size_t CPackResource::GetDecompressedSize() 
{
	return m_info.decompress_size;
}

size_t CPackResource::GetVersion() 
{
	return m_info.seed;
}

FILETIME CPackResource::GetCreationTime() 
{
	return m_info.ft[0];
}

FILETIME CPackResource::GetLastAccessTime() 
{
	return m_info.ft[2];
}

FILETIME CPackResource::GetLastWriteTime() 
{
	return m_info.ft[4];
}

size_t CPackResource::GetDecompressedContent(char * pBuffer, size_t size) 
{
	vector<char> compressContent(m_info.compress_size);

	GetCompressedContent(&compressContent[0], m_info.compress_size);

	unsigned long decodeLen = size;

	CUtility::ZlibUncompress(pBuffer, &decodeLen, &compressContent[0], m_info.compress_size);

	return decodeLen;
}

size_t CPackResource::GetCompressedContent(char * pBuffer, size_t size) 
{
	m_spFile->Seek(m_info.offset, FILE_BEGIN);
	int tmp = m_spFile->Read( pBuffer, m_info.compress_size );
	if (tmp != m_info.compress_size)
	{
		// 文件读取错误
		return 0;
	}

	// 直接读取的是加密的，需要解密
	CUtility::Decrypt(pBuffer, tmp, m_info.seed);

	return tmp;
}

void CPackResource::Release()
{
	// 资源是CPackResourceSet统一释放的
}