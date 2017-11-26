#ifndef IDC_STATIC
#define IDC_STATIC (-1)
#endif

#define VER_FILEVERSION             1,0,7,0
#define VER_FILEVERSION_STR         "1.0.7.0\0"

#define VER_PRODUCTVERSION          1,0,7,0
#define VER_PRODUCTVERSION_STR      "1.0.7.0\0"

#ifndef DEBUG
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

#ifdef _WIN64
#define VER_FILE_DESC               "Mabinogi Package File Management API Library for .NET (x64)"
#else
#define VER_FILE_DESC               "Mabinogi Package File Management API Library for .NET (x86)"
#endif
