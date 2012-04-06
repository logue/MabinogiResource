#include "StdAfx.h"
#include "NullProgressMonitor.h"


NullProgressMonitor::NullProgressMonitor(void) : m_bCanceled(false)
{
}


NullProgressMonitor::~NullProgressMonitor(void)
{
}

void NullProgressMonitor::BeginWork( LPCTSTR lpszName, int totalWork )
{

}

void NullProgressMonitor::Worked( int work )
{

}

void NullProgressMonitor::Done()
{

}

void NullProgressMonitor::SetTaskName( LPCTSTR name )
{

}

void NullProgressMonitor::SetSubTaskName( LPCTSTR lpszName )
{

}

bool NullProgressMonitor::IsCanceled()
{
	return m_bCanceled;
}

void NullProgressMonitor::SetCanceled( bool value )
{
	m_bCanceled = value;
}
