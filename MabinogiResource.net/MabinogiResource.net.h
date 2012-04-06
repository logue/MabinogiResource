// MabinogiResource.net.h

#pragma once
#include <Windows.h>
#include "../MabinogiResource/MabinogiResource.h"
#include <vector>
using namespace std;
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace MabinogiResource 
{

	public ref class PackResource
	{
	public:
		//获取文件的名字
		String^	GetName()		{return m_Name;}
		//获取文件的大小
		size_t	GetSize()		{return m_Size;}
		//获取文件的数据
		bool	GetData(array<Byte>^ buffer);
		//关闭文件数据
		void	Close();
	private:
		PACK_RESOURCE_HANDLE	m_Handle;
		String^					m_Name;
		size_t					m_Size;
	public:
		PackResource(PACK_RESOURCE_HANDLE handle);
		~PackResource();
	};

	// 文件集合
	public ref class PackResourceSet
	{
	public:
		//获取资源集中文件的数量
		size_t		GetFileCount()		{return m_FileCount;}
		//获取指定索引的文件
		PackResource^	GetFileByIndex(size_t index);
		//获取指定名称的文件
		PackResource^	GetFileByName(String^ name);
		//关闭资源集
		void		Close();
		//析构函数
		~PackResourceSet();
	private:
		PACK_RESOURCE_SET_HANDLE	m_Handle;
		size_t		m_FileCount;
	private:
		PackResourceSet(PACK_RESOURCE_SET_HANDLE handle);
	public:
		//从pack文件创建资源集
		static PackResourceSet^	CreateFromFile(String^ fileName);
		//从pack文件夹创建资源集
		static PackResourceSet^	CreateFromFolder(String^ fileName);
	};

	// 文件集合创建器
	public ref class PackResourceSetCreater
	{
	public:
		//添加一个要打包的文件。参数：文件在pack包中的名称，文件在硬盘上的原始路径
		bool	AddFile(String^ fileName,String^ filePath);
		//打包,参数：要生成的pack文件的版本，生成的pack文件的保存地址
		bool	CreatePack(size_t version,String^ filePath);
	private:
		vector<PACK_RESOURCE_HANDLE>*	m_List;
		size_t	m_Version;
	public:
		PackResourceSetCreater(size_t version);
		~PackResourceSetCreater();
	};
}
