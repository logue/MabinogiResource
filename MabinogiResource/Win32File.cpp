#include "StdAfx.h"
#include "Win32File.h"

CWin32File::CWin32File()
{
	m_hFile = NULL;
}

CWin32File::CWin32File(LPCTSTR lpszFile)
{
	Open(lpszFile, false);
}

CWin32File::CWin32File( LPCTSTR lpszFile, bool write )
{
	Open(lpszFile, write);
}
CWin32File::~CWin32File(void)
{
	Close();
}

UINT CWin32File::Read( void* lpBuf, UINT nCount ) const
{
	DWORD NumberOfBytesRead = 0;
	BOOL bRet = ::ReadFile(m_hFile, lpBuf, nCount, &NumberOfBytesRead, 0);
	if (bRet == 0)
	{
		return -1;
	}
	
	return NumberOfBytesRead;
}

UINT CWin32File::Write( void* lpBuf, UINT nCount ) const
{
	DWORD NumberOfBytesWritten = 0;
	BOOL bRet = ::WriteFile(m_hFile, lpBuf, nCount, &NumberOfBytesWritten, 0);
	if (bRet == 0)
	{
		return -1;
	}

	return NumberOfBytesWritten;
}

ULONGLONG CWin32File::GetLength() const
{
	LARGE_INTEGER liSize;
	BOOL bRet = ::GetFileSizeEx(m_hFile, &liSize);
	if ( bRet == 0)
	{
		return -1;
	}
	return liSize.QuadPart;
}

ULONGLONG CWin32File::Seek( LONGLONG lOff, UINT nFrom ) const
{
	LARGE_INTEGER liOffset;
	liOffset.QuadPart = lOff;
	LARGE_INTEGER liResult;
	BOOL bRet = ::SetFilePointerEx(m_hFile, liOffset, &liResult, nFrom);
	if ( bRet == 0)
	{
		throw -1;
	}
	return liResult.QuadPart;
}

void CWin32File::Open( LPCTSTR lpszFile , bool write)
{
	DWORD dwDesiredAccess = GENERIC_READ;
	DWORD dwCreationDisposition = OPEN_EXISTING;
	if (write)
	{
		dwCreationDisposition = CREATE_ALWAYS;
		dwDesiredAccess |= GENERIC_WRITE;
	}
	HANDLE hFile = ::CreateFile(lpszFile, dwDesiredAccess, FILE_SHARE_READ, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, 0 );
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_hFile = hFile;
	}
}

void CWin32File::Close()
{
	if (m_hFile != 0)
	{
		::CloseHandle(m_hFile);
		m_hFile = 0;
	}
}

bool CWin32File::IsOK() const
{
	return m_hFile != 0;
}

