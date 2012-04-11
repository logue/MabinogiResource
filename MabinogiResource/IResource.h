#pragma once

#include "ExportMacro.h"
#include "IObject.h"

class MABINOGIRESOURCE_API IResource : public IObject
{
public:
	// Constructor
	IResource(void){}

	// Destructor
	virtual ~IResource(void){}

	// The entity's full name, is a relative path, such as db / ss.xml.
	virtual LPCTSTR GetName() = 0;

	// Decompressed content. (uncrypted)
	virtual size_t GetDecompressedContent(char * pBuffer, size_t size) = 0;

	// Compressed content .(uncrypted)
	virtual size_t GetCompressedContent(char * pBuffer, size_t size, int level) = 0;

	// Compressed content size.
	virtual size_t GetCompressedSize() = 0;

	// Decompressed content size.
	virtual size_t GetDecompressedSize() = 0;

	// Return the version. The higher the number, the new version.
	virtual size_t GetVersion() = 0;

	// Created time.
	virtual FILETIME GetCreationTime() = 0;

	// Last accessed time.
	virtual FILETIME GetLastAccessTime() = 0;

	// Last modified time.
	virtual FILETIME GetLastWriteTime() = 0;

	// Create a resource entry from the file
	static IResource * CreateResourceFromFile(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version, int level);
};
