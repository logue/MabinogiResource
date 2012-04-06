#pragma once

#pragma pack(1)

struct PACKAGE_HEADER
{
	char signature[8];	// 'P' 'A' 'C' 'K' 0x02 0x01 0x00 0x00
	unsigned long d1;	// 1
	unsigned long sum;	// 文件总数
	FILETIME ft1;
	FILETIME ft2;
	char path[480];		// 'd' 'a' 't' 'a' '\' 0x00 ...

};

struct PACKAGE_LIST_HEADER 
{
	unsigned long sum;				// 文件总数
	unsigned long list_header_size;	// 文件头列表大小(包括了空白区域)
	unsigned long blank_size;		// 文件列表和数据区之间的空白区域大小 
	unsigned long data_section_size;		// 数据区大小
	char zero[16];

};

struct ITEM_NAME
{
	char len_or_type;
	union
	{
		// len_or_type == 0x05的时候
		struct  
		{
			unsigned long len;
			char  sz_ansi_name2[1];
		};

		// 普通情况下的文件名
		char sz_ansi_name[1];
	};
};

struct ITEM_INFO
{
	unsigned long seed;
	unsigned long zero;
	unsigned long offset;
	unsigned long compress_size;
	unsigned long decompress_size;
	unsigned long is_compressed;
	FILETIME ft[5];
};

#pragma pack()