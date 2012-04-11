#include "StdAfx.h"
#include "FileResource.h"

#include <vector>
using namespace std;

#include "Utility.h"

//////////////////////////////////////////////////////////////////////////

IResource * IResource::CreateResourceFromFile(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version, int level)
{
	return new CFileResource(lpszFile, lpszResourceName, version, level);
}
//////////////////////////////////////////////////////////////////////////
CFileResource::CFileResource(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version, int level)
{
	m_version = version;
	m_file.Open(lpszFile, false);
	m_name = lpszResourceName;

	WIN32_FIND_DATA wfd;
	HANDLE hFind = ::FindFirstFile(lpszFile, &wfd);
	m_ftCreation = wfd.ftCreationTime;
	m_ftLastAccess = wfd.ftLastAccessTime;
	m_ftLastWrite = wfd.ftLastWriteTime;
	m_decompressedSize = wfd.nFileSizeLow;
	m_compressedSize = 0;
	::FindClose(hFind);
}

CFileResource::~CFileResource(void)
{
}

LPCTSTR CFileResource::GetName() 
{
	return m_name.c_str();
}

size_t CFileResource::GetCompressedSize() 
{
	// 如果压缩大小还未知则给出一个可能值
	if (m_compressedSize == 0)
	{
		return GetDecompressedSize() + 1024;
	}
	return m_compressedSize;
}

size_t CFileResource::GetVersion() 
{
	return m_version;
}

FILETIME CFileResource::GetCreationTime() 
{
	return m_ftCreation;
}

FILETIME CFileResource::GetLastAccessTime() 
{
	return m_ftLastAccess;
}

FILETIME CFileResource::GetLastWriteTime() 
{
	return m_ftLastWrite;
}

size_t CFileResource::GetDecompressedContent(char * pBuffer, size_t size) 
{
	m_file.Seek(0, FILE_BEGIN);
	return m_file.Read(pBuffer, size);

}

size_t CFileResource::GetCompressedContent(char * pBuffer, size_t size, int level) 
{
	vector<char> decompressContent(m_decompressedSize);

	GetDecompressedContent(&decompressContent[0], m_decompressedSize);

	unsigned long encodeLen = size;

	if (CUtility::ZlibCompress(pBuffer, &encodeLen, &decompressContent[0], m_decompressedSize, level))
	{
		m_compressedSize = encodeLen;
	}

	return encodeLen;
}

size_t CFileResource::GetDecompressedSize() 
{
	return m_decompressedSize;
}

void CFileResource::Release()
{
	delete this;
}