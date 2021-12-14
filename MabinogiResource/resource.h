#ifndef IDC_STATIC
#define IDC_STATIC (-1)
#endif

#define IDS_MAKE_PACK_FILE                      40000
#define IDS_INIT_PACK_HEADER                    40001
#define IDS_WRITE_PACK_HEADER                   40002
#define IDS_WRITE_FILE_LIST                     40003

#define VER_FILEVERSION             1,0,10,0
#define VER_FILEVERSION_STR         "1.0.10.0\0"

#define VER_PRODUCTVERSION          1,0,10,0
#define VER_PRODUCTVERSION_STR      "1.0.10.0\0"

#ifndef DEBUG
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

#if _M_X64
#define VER_FILE_DESC               "Mabinogi Package File Management API Library (x64)"
#else
#define VER_FILE_DESC               "Mabinogi Package File Management API Library (x86)"
#endif

#define VER_COPYRIGHT               "Copyright (C) 2011 DarknessTM / 2012,2014,2017,2019,2021 Logue"
