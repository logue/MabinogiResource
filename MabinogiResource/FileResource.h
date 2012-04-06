#pragma once
#include "iresource.h"

#include "tstring.h"
#include "Win32File.h"

using namespace std;

class CFileResource : public IResource
{
public:
	// 从一个文件创建IResource对象
	CFileResource(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version);

	virtual ~CFileResource(void);

	// 当前实体的全名，为相对路径，如 db/ss.xml
	virtual LPCTSTR GetName() ;

	// 返回解压后内容，每次返回新的容器
	virtual size_t GetDecompressedContent(char * pBuffer, size_t size) ;

	// 返回解压前内容，每次返回新的容器
	virtual size_t GetCompressedContent(char * pBuffer, size_t size) ;

	// 返回压缩后大小
	virtual size_t GetCompressedSize() ;

	// 返回压缩前的大小
	virtual size_t GetDecompressedSize() ;

	// 返回版本，数字越大，版本越高
	virtual size_t GetVersion() ;

	// 返回创建时间
	virtual FILETIME GetCreationTime() ;

	// 返回最后访问时间
	virtual FILETIME GetLastAccessTime() ;

	// 返回最后写入时间
	virtual FILETIME GetLastWriteTime() ;

	virtual void Release();
protected:
	CWin32File m_file;
	tstring m_name;
	size_t m_compressedSize;
	size_t m_decompressedSize;
	size_t m_version;
	FILETIME m_ftCreation;
	FILETIME m_ftLastAccess;
	FILETIME m_ftLastWrite;
};
