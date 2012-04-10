// MabinogiResource.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MabinogiResource.h"

#include "IResource.h"
#include "IProgressMonitor.h"
#include "PackResourceSet.h"
#include "ResourceFileSystem.h"
#include "FileResource.h"
#include "TCHAR.H"

struct SReourceSet : public PACK_RESOURCE_SET
{
	SReourceSet(IResourceSet * pResourceSet)
	{
		m_pResourceSet = pResourceSet;
	};

	~SReourceSet()
	{
		delete m_pResourceSet;
		m_pResourceSet = NULL;
	}
	IResourceSet * m_pResourceSet;
};

struct SResource : public PACK_RESOURCE
{
	SResource(IResource * pResource)
	{
		m_pResource = pResource;
	};
	~SResource()
	{
		delete m_pResource;
		m_pResource = NULL;
	}
	IResource * m_pResource;
};

class ProgressMonitor : public IProgressMonitor
{
public:
	ProgressMonitor(ProgressMonitorProc proc, DWORD dwParameter) : m_pfnProc(proc), m_dwParameter(dwParameter), m_bCanceled(false)
	{

	}

	virtual ~ProgressMonitor()
	{

	}

	// 开始一个作业
	virtual void BeginWork(LPCTSTR lpszName, int totalWork )
	{
		if (m_pfnProc == NULL)
		{
			return;
		}
		ProgressMonitorData data;
		data.type = PROGRESS_MONITOR_BEGIN_TASK;
		data.dwParamter = m_dwParameter;
		data.content.beginTask.lpszTaskName = lpszName;
		data.content.beginTask.totalWork = totalWork;
		SetCanceled(!m_pfnProc(&data));
	}

	// 增加作业步进
	virtual void Worked(int work)
	{
		if (m_pfnProc == NULL)
		{
			return;
		}
		ProgressMonitorData data;
		data.type = PROGRESS_MONITOR_WORKED;
		data.dwParamter = m_dwParameter;
		data.content.worked.work = work;
		SetCanceled(!m_pfnProc(&data));
	}

	// 结束作业
	virtual void Done()
	{
		if (m_pfnProc == NULL)
		{
			return;
		}
		ProgressMonitorData data;
		data.type = PROGRESS_MONITOR_DONE;
		data.dwParamter = m_dwParameter;
		SetCanceled( !m_pfnProc(&data));
	}

	// 设置当前作业的名称
	virtual void SetTaskName(LPCTSTR name)
	{
		if (m_pfnProc == NULL)
		{
			return;
		}
		ProgressMonitorData data;
		data.type = PROGRESS_MONITOR_SET_TASK_NAME;
		data.dwParamter = m_dwParameter;
		data.content.setTaskName.lpszName = name;
		SetCanceled( !m_pfnProc(&data));
	}

	// 设置当前作业的副作业名称
	virtual void SetSubTaskName(LPCTSTR lpszName)
	{
		if (m_pfnProc == NULL)
		{
			return;
		}
		ProgressMonitorData data;
		data.type = PROGRESS_MONITOR_SET_SUB_TASK_NAME;
		data.dwParamter = m_dwParameter;
		data.content.setSubTaskName.lpszName = lpszName;
		SetCanceled( !m_pfnProc(&data));
	}

	// 返回当前作业是否正在取消中
	virtual bool IsCanceled()
	{
		return m_bCanceled;
	}

	// 设置当前作业是否取消
	virtual void SetCanceled(bool value)
	{
		if (m_bCanceled != value)
		{
			m_bCanceled = value;
			// TODO
		}

	}

private:
	ProgressMonitorProc m_pfnProc;
	DWORD m_dwParameter;
	bool m_bCanceled;
};

MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder( LPCTSTR lpszFolder )
{
	IResourceSet * pSet = IResourceSet::CreateResourceSetFromFolder(lpszFolder);
	if (pSet != 0)
	{
		return new SReourceSet(pSet);
	}

	return 0;
}

MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile( LPCTSTR lpszFile )
{
	IResourceSet * pSet = IResourceSet::CreateResourceSetFromFile(lpszFile);
	if (pSet != 0)
	{
		return new SReourceSet(pSet);
	}

	return 0;
}

MABINOGIRESOURCE_API void CloseResourceSet( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	delete hResourceSet;
}

MABINOGIRESOURCE_API int ResourceSet_FindResourceIndex( PACK_RESOURCE_SET_HANDLE hResourceSet, LPCTSTR lpszName )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_pResourceSet->FindResourceIndex(lpszName);
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE ResourceSet_GetResource( PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	IResource * pRes = pSSet->m_pResourceSet->GetResource(index);
	return new SResource(pRes);
}

MABINOGIRESOURCE_API size_t ResourceSet_GetResourceCount( PACK_RESOURCE_SET_HANDLE hResourceSet )
{
	SReourceSet * pSSet = (SReourceSet *) hResourceSet;
	return pSSet->m_pResourceSet->GetResourceCount();
}

MABINOGIRESOURCE_API void CloseResource( PACK_RESOURCE_HANDLE hResource )
{
	delete hResource;
}

//MABINOGIRESOURCE_API LPCSTR GetName( PACK_RESOURCE_HANDLE hResource )
//{
//	SResource * pSRes = (SResource *) hResource;
//	return pSRes->m_spResource->GetName().c_str();
//}

MABINOGIRESOURCE_API size_t Resource_GetDecompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size )
{
	SResource * pSRes = (SResource *) hResource;

	return pSRes->m_pResource->GetDecompressedContent((char*)lpBuffer, size);
}

MABINOGIRESOURCE_API size_t Resource_GetCompressedContent( PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size , int level)
{
	SResource * pSRes = (SResource *) hResource;

	return pSRes->m_pResource->GetCompressedContent((char*)lpBuffer, size, level);
}

MABINOGIRESOURCE_API size_t Resource_GetCompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetCompressedSize();
}

MABINOGIRESOURCE_API size_t Resource_GetDecompressedSize( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetDecompressedSize();
}

MABINOGIRESOURCE_API size_t Resource_GetVersion( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetVersion();
}

MABINOGIRESOURCE_API FILETIME Resource_GetCreationTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetCreationTime();
}

MABINOGIRESOURCE_API FILETIME Resource_GetLastAccessTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetLastAccessTime();
}

MABINOGIRESOURCE_API FILETIME Resource_GetLastWriteTime( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return pSRes->m_pResource->GetLastWriteTime();
}

MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile( LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version)
{
	IResource * pRes = IResource::CreateResourceFromFile(lpszFile, lpszResourceName, version, 0);
	return new SResource(pRes);
}


MABINOGIRESOURCE_API void PackResources( PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile, ProgressMonitorProc proc, DWORD dwParameter, int level)
{

	vector<IResource*> resources;
	for (size_t i = 0;i < length;i++)
	{
		SResource * pSres = (SResource *)hResourceArray[i];
		resources.push_back(pSres->m_pResource);
	}

	ProgressMonitor monitor(proc, dwParameter);

	IResourceSet::PackResources(&resources[0], resources.size(), version, lpszPackFile, &monitor, level);

}

MABINOGIRESOURCE_API int Resource_GetResourceName( PACK_RESOURCE_HANDLE hResource, LPTSTR lpszBuffer, int nBuffer )
{
	SResource * pSRes = (SResource *) hResource;
	int nLength = _tcslen( pSRes->m_pResource->GetName() );
	nLength = (nLength > nBuffer) ? nBuffer : nLength;

	_tcsncpy_s(lpszBuffer, nBuffer,pSRes->m_pResource->GetName(), nBuffer);

	return nLength;
}

MABINOGIRESOURCE_API int Resource_GetResourceNameLength( PACK_RESOURCE_HANDLE hResource )
{
	SResource * pSRes = (SResource *) hResource;
	return lstrlen(pSRes->m_pResource->GetName());
}