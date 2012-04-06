#pragma once
#include "iprogressmonitor.h"
class NullProgressMonitor : public IProgressMonitor
{
public:
	NullProgressMonitor(void);
	virtual ~NullProgressMonitor(void);

	// 开始一个作业
	virtual void BeginWork(LPCTSTR lpszName, int totalWork );

	// 增加作业步进
	virtual void Worked(int work);

	// 结束作业
	virtual void Done();

	// 设置当前作业的名称
	virtual void SetTaskName(LPCTSTR name);

	// 设置当前作业的副作业名称
	virtual void SetSubTaskName(LPCTSTR lpszName);

	// 返回当前作业是否正在取消中
	virtual bool IsCanceled();

	// 设置当前作业是否取消
	virtual void SetCanceled(bool value);

private:
	bool m_bCanceled;
};

