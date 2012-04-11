#pragma once

#include "ExportMacro.h"

class MABINOGIRESOURCE_API IProgressMonitor
{
public:
	// Constructor
	IProgressMonitor(void){}

	// Destructor
	virtual ~IProgressMonitor(void){}

	// Start a job
	virtual void BeginWork(LPCTSTR lpszName, int totalWork ) = 0;

	// Increase operational step
	virtual void Worked(int work) = 0;

	// End of the job
	virtual void Done() = 0;

	// Set the name of the current job
	virtual void SetTaskName(LPCTSTR name) = 0;

	// Set the sub name of the current job
	virtual void SetSubTaskName(LPCTSTR lpszName) = 0;

	// Back to the current job is being canceled
	virtual bool IsCanceled() = 0;

	// Set the current job whether to cancel
	virtual void SetCanceled(bool value) = 0;

private:
	IProgressMonitor(IProgressMonitor const & other);
	IProgressMonitor& operator=(IProgressMonitor const & other);
};
