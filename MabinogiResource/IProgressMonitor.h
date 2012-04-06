#pragma once

#include "ExportMacro.h"

class MABINOGIRESOURCE_API IProgressMonitor
{
public:

	IProgressMonitor(void)
	{
	}

	virtual ~IProgressMonitor(void)
	{
	}


	// 开始一个作业
	virtual void BeginWork(LPCTSTR lpszName, int totalWork ) = 0;

	// 增加作业步进
	virtual void Worked(int work) = 0;

	// 结束作业
	virtual void Done() = 0;

	// 设置当前作业的名称
	virtual void SetTaskName(LPCTSTR name) = 0;

	// 设置当前作业的副作业名称
	virtual void SetSubTaskName(LPCTSTR lpszName) = 0;

	// 返回当前作业是否正在取消中
	virtual bool IsCanceled() = 0;

	// 设置当前作业是否取消
	virtual void SetCanceled(bool value) = 0;

private:
	IProgressMonitor(IProgressMonitor const & other);
	IProgressMonitor& operator=(IProgressMonitor const & other);
};
