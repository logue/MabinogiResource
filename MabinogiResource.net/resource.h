#ifndef IDC_STATIC
#define IDC_STATIC (-1)
#endif

#define VER_FILEVERSION             1,0,8,0
#define VER_FILEVERSION_STR         "1.0.8.0\0"

#define VER_PRODUCTVERSION          1,0,8,0
#define VER_PRODUCTVERSION_STR      "1.0.8.0\0"

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

#define VER_COPYRIGHT               "Copyright (C) 2011 DarknessTM / 2012,2014,2017,2019 Logue"
