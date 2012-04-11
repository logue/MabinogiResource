#include "stdafx.h"
#include "MabinogiResource.net.h"
#include <string>
#include <vcclr.h>
using namespace std;
#pragma comment(lib,"MabinogiResource.lib")

namespace MabinogiResource
{
	string	StringTostring(String^ text)
	{
		UTF8Encoding^ utf8 = gcnew UTF8Encoding();
		array<Byte>^ chars=utf8->GetBytes(text);
		string str;
		for(int i=0;i<chars->Length;++i)
		{
			str+=chars[i];
		}
		return str;
	}

	wstring	StringToString(String^ text)
	{
		pin_ptr<const wchar_t> str = PtrToStringChars(text);
		return str;
	}

	string	ToUTF8(const wchar_t* text)
	{
		size_t len=wcslen(text);
		// Get output buffer length
		int		buffersize=WideCharToMultiByte(CP_UTF8,0,text,len,0,0,0,0);
		char*	g_StringBuffer=new char[buffersize+1];
		WideCharToMultiByte(CP_UTF8,0,text,(int)len,g_StringBuffer,buffersize+1,0,0);
		g_StringBuffer[buffersize]=0;
		string str= g_StringBuffer;
		delete [] g_StringBuffer;
		return str;
	}

	String^	FromUTF8(const char* text)
	{
		if(text==0)
		{
			return gcnew String(L"");
		}
		int len=strlen(text);
		wchar_t* buffer=new wchar_t[len+1];
		int i=MultiByteToWideChar(CP_UTF8, 0, text,len, buffer, len+1);
		buffer[len]=0;
		String^ str= gcnew String(buffer);
		delete [] buffer;
		return str;
	}
	//========================================================================================
	PackResource::PackResource( PACK_RESOURCE_HANDLE handle )
	{
		m_Handle=handle;
		if(m_Handle!=NULL)
		{
			wchar_t name[260];
			ZeroMemory(name,260);
			Resource_GetResourceName(m_Handle,name,260);
			m_Name = gcnew String(name);
			m_Size = Resource_GetDecompressedSize(m_Handle);
			m_version = Resource_GetVersion(m_Handle);
/*
			m_created = Resource_GetCreationTime(m_Handle);
			m_accessed = Resource_GetLastAccessTime(m_Handle);
			m_modified = Resource_GetLastWriteTime(m_Handle);
*/
		}
		else
		{
			m_Name = gcnew String(L"");
			m_Size = 0;
			m_version = 0;
		}
	}

	PackResource::~PackResource()
	{
		Close();
	}
	bool PackResource::GetData( array<Byte>^ buffer )
	{
		if(m_Handle==NULL) return false;
		if(buffer->Length<(int)m_Size) return false;
		pin_ptr<Byte> p =  &buffer[ 0 ];
		Byte * np = p;
		Resource_GetDecompressedContent(m_Handle,np,m_Size);
		return true;
	}

	void PackResource::Close()
	{
		if(m_Handle!=NULL)
		{
			CloseResource(m_Handle);
			m_Handle=NULL;
		}
	}
	//========================================================================================
	PackResourceSetCreater::PackResourceSetCreater(size_t version, int level)
	{
		m_Version=version;
		m_level=level;
		m_List=new vector<PACK_RESOURCE_HANDLE>;
	}

	PackResourceSetCreater::~PackResourceSetCreater()
	{
		if (m_List)
		{
			for(size_t i=0;i<m_List->size();++i)
			{
				CloseResource(m_List->at(i));
			}
			delete m_List;
			m_List=NULL;
		}
	}

	bool PackResourceSetCreater::AddFile( String^ fileName, String^ filePath )
	{
		pin_ptr<const wchar_t> path = PtrToStringChars(filePath);
		pin_ptr<const wchar_t> name = PtrToStringChars(fileName);
		PACK_RESOURCE_HANDLE hRes = CreateResourceFromFile(path, name, m_Version);
		if(hRes!=NULL)
		{
			m_List->push_back(hRes);
		}
		return true;
	}

	bool PackResourceSetCreater::CreatePack( String^ outputPath )
	{
		pin_ptr<const wchar_t> path = PtrToStringChars(outputPath);
		
		if(m_List->size()==0)
		{
			PackResources(NULL,0, m_Version, path, 0, 0, 0);
		}
		else
		{
			PackResources(&m_List->operator[](0),m_List->size(), m_Version, path, 0, 0, m_level);
		}		
		return true;
	}

	//========================================================================================
	PackResourceSet::PackResourceSet( PACK_RESOURCE_SET_HANDLE handle )
	{
		m_Handle=handle;
		if(m_Handle)
		{
			m_FileCount=ResourceSet_GetResourceCount(m_Handle);
		}
		else
		{
			m_FileCount=0;
		}
	}

	PackResourceSet::~PackResourceSet()
	{
		Close();
	}

	void PackResourceSet::Close()
	{
		if(m_Handle!=NULL)
		{
			CloseResourceSet(m_Handle);
			m_Handle=NULL;
		}
	}

	PackResource^ PackResourceSet::GetFileByIndex( size_t index )
	{
		if(index>=m_FileCount) return nullptr;
		PACK_RESOURCE_HANDLE h=ResourceSet_GetResource(m_Handle,index);
		if(h==NULL)
		{
			return nullptr;
		}
		return gcnew PackResource(h);
	}

	PackResource^ PackResourceSet::GetFileByName( String^ name )
	{
		int index=ResourceSet_FindResourceIndex(m_Handle,StringToString(name).c_str());
		if(index<0) return nullptr;
		return GetFileByIndex(index);
	}

	PackResourceSet^ PackResourceSet::CreateFromFile( String^ fileName )
	{
		pin_ptr<const wchar_t> szResName = PtrToStringChars(fileName);
		PACK_RESOURCE_SET_HANDLE h=CreateResourceSetFromFile(szResName);
		if(h==NULL) return nullptr;
		return gcnew PackResourceSet(h);
	}

	PackResourceSet^ PackResourceSet::CreateFromFolder( String^ fileName )
	{
		pin_ptr<const wchar_t> szResName = PtrToStringChars(fileName);
		PACK_RESOURCE_SET_HANDLE h=CreateResourceSetFromFolder(szResName);
		if(h==NULL) return nullptr;
		return gcnew PackResourceSet(h);
	}
}