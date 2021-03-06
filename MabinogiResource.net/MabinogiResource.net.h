// MabinogiResource.net.h

#pragma once
#include "IProgressMonitor.h"
#include "MabinogiResource.h"
#include <Windows.h>
#include <vector>

using namespace std;
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Diagnostics::Contracts;

namespace MabinogiResource {

public
ref class PackResource {
private:
  PACK_RESOURCE_HANDLE m_Handle;
  String ^ m_Name;
  size_t m_Size;
  size_t m_Version;
  System::DateTime m_created;
  System::DateTime m_accessed;
  System::DateTime m_modified;

public:
  // Constructor
  PackResource(PACK_RESOURCE_HANDLE handle);
  // Destructor
  ~PackResource();

  // Get file name
  String ^ GetName() { return m_Name; }
      // Get file size
      size_t GetSize() {
    return m_Size;
  }
  // Get file version
  size_t GetVersion() { return m_Version; }
  // Get file content
  size_t GetData(cli::array<Byte> ^ buffer);

  // Get file created time
  System::DateTime GetCreated() { return m_created; }
  // Get file last accessed time
  System::DateTime GetAccessed() { return m_accessed; }
  // Get file last modified time
  System::DateTime GetModified() { return m_modified; }

  // Close the file data
  void Close();
};

// Package File
public
ref class PackResourceSet {
private:
  PACK_RESOURCE_SET_HANDLE m_Handle;
  size_t m_FileCount;

public:
  // Constructor
  PackResourceSet(PACK_RESOURCE_SET_HANDLE handle);
  // Destructor
  ~PackResourceSet();

  // Count resource files
  size_t GetFileCount() { return m_FileCount; }
  // Get resource file by index.
  PackResource ^ GetFileByIndex(size_t index);
  // Get resource file by file name.
  PackResource ^ GetFileByName(String ^ name);

  // Create a set of resources from the pack file
  static PackResourceSet ^ CreateFromFile(String ^ fileName);
  // Create a set of resources from the pack files folder
  static PackResourceSet ^ CreateFromFolder(String ^ fileName);

  // Close resources
  void Close();
};

// Package file creator
public
ref class PackResourceSetCreater {
private:
  vector<PACK_RESOURCE_HANDLE> *m_List;
  size_t m_Version;
  int m_level;

public:
  // Constructor
  // Parameters:
  //		version : pack file Version
  //		level   : compress level
  PackResourceSetCreater(size_t version, int level);
  // Destructor
  ~PackResourceSetCreater();

  // Add file to Package file.
  // Parameters:
  //		fileName : the name of the file in the pack
  //		filePath : package file on your hard drive the original path
  bool AddFile(String ^ fileName, String ^ filePath);
  // Create Package file.
  // Parameters:
  //		outputPath : Save path of generated pack file
  bool CreatePack(String ^ outputPath);
};

public
ref class IProgressMonitor {
public:
  // Constructor
  IProgressMonitor(void) {}

  // Destructor
  virtual ~IProgressMonitor(void) {}

  // Start a job
  virtual void BeginWork(LPCTSTR lpszName, int totalWork) = 0;

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
  // IProgressMonitor(IProgressMonitor const & other);
  // IProgressMonitor& operator=(IProgressMonitor const & other);
};
}
