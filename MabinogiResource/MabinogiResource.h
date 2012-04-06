#pragma once

#include "ExportMacro.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PACK_RESOURCE_SET {};
struct PACK_RESOURCE {};

typedef PACK_RESOURCE_SET* PACK_RESOURCE_SET_HANDLE;
typedef PACK_RESOURCE* PACK_RESOURCE_HANDLE;

#define PROGRESS_MONITOR_BEGIN_TASK			0
#define PROGRESS_MONITOR_WORKED				1
#define PROGRESS_MONITOR_DONE				2
#define PROGRESS_MONITOR_SET_TASK_NAME		3
#define PROGRESS_MONITOR_SET_SUB_TASK_NAME	4

struct ProgressMonitorData 
{
	int type;
	union
	{
		struct _BeginTask 
		{
			LPCTSTR lpszTaskName;
			int totalWork;
		} beginTask;
		struct _Worked
		{
			int work;
		} worked;
		struct _Done 
		{
	
		} done;

		struct _SetTaskName
		{
			LPCTSTR lpszName;
		} setTaskName;

		struct _SetSubTaskName
		{
			LPCTSTR lpszName;
		} setSubTaskName;
	} content;
	DWORD dwParamter;
};
// Callback function in the suppression of the package file
// False is interrupted.
typedef bool (*ProgressMonitorProc)(ProgressMonitorData * pData);

//////////////////////////////////////////////////////////////////////////
// Create a set of resources on and off the set of resources manage
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder(LPCTSTR lpszFolder);
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile(LPCTSTR lpszFile);
MABINOGIRESOURCE_API void CloseResourceSet(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

// Create a resource from a file
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version);

// The release of a resource reference
MABINOGIRESOURCE_API void CloseResource(PACK_RESOURCE_HANDLE hResource);

//////////////////////////////////////////////////////////////////////////
// Find to specify the full name of the resource
MABINOGIRESOURCE_API int ResourceSet_FindResourceIndex(PACK_RESOURCE_SET_HANDLE hResourceSet, LPCTSTR lpszName);

// Access to resource
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE ResourceSet_GetResource(PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index);

// Total number of resources
MABINOGIRESOURCE_API size_t ResourceSet_GetResourceCount(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// The full name of the current entity, is a relative path, such as in db / ss.xml
MABINOGIRESOURCE_API int Resource_GetResourceName(PACK_RESOURCE_HANDLE hResource, LPTSTR lpszBuffer, int nBuffer);

// Resource Name Length
MABINOGIRESOURCE_API int Resource_GetResourceNameLength(PACK_RESOURCE_HANDLE hResource);

// Decompressed Content
MABINOGIRESOURCE_API size_t Resource_GetDecompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// Compressed Content
MABINOGIRESOURCE_API size_t Resource_GetCompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// Compressed size
MABINOGIRESOURCE_API size_t Resource_GetCompressedSize(PACK_RESOURCE_HANDLE hResource);

// Before compression size
MABINOGIRESOURCE_API size_t Resource_GetDecompressedSize(PACK_RESOURCE_HANDLE hResource);

// Package Version
MABINOGIRESOURCE_API size_t Resource_GetVersion(PACK_RESOURCE_HANDLE hResource);

// Created
MABINOGIRESOURCE_API FILETIME Resource_GetCreationTime(PACK_RESOURCE_HANDLE hResource);

// Last accessed
MABINOGIRESOURCE_API FILETIME Resource_GetLastAccessTime(PACK_RESOURCE_HANDLE hResource);

// Last modified
MABINOGIRESOURCE_API FILETIME Resource_GetLastWriteTime(PACK_RESOURCE_HANDLE hResource);	
//////////////////////////////////////////////////////////////////////////

// Save as a pack file.
MABINOGIRESOURCE_API void PackResources(PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile, ProgressMonitorProc proc, DWORD dwParameter);

#ifdef __cplusplus
}
#endif

