#pragma once

class CWin32File
{
public:
	CWin32File();
	CWin32File(LPCTSTR lpszFile);
	CWin32File(LPCTSTR lpszFile, bool write);
	~CWin32File(void);

	bool IsOK() const;
	UINT Read(void* lpBuf, UINT nCount) const;
	UINT Write(void* lpBuf, UINT nCount) const;
	ULONGLONG GetLength() const;
	ULONGLONG Seek(LONGLONG lOff, UINT nFrom) const;
	void Open(LPCTSTR lpszFile, bool write);
	void Close();

private:
	HANDLE m_hFile;
};
