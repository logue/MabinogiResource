// stdafx.h : 標準のシステム インクルード ファイルのインクルードファイル、
// または参照回数が多く、かつあまり変更されない、プロジェクト専用の
// インクルードファイルを記述します。

#pragma once

#include "targetver.h"

// Windowsヘッダーから使用されていない部分を除外します。
#define WIN32_LEAN_AND_MEAN

// Windows ヘッダー ファイル:
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include <ntstatus.h>
#include <winternl.h>

// C ランタイム ヘッダー ファイル
#include <algorithm>
#include <iostream>
#include <malloc.h>
#include <map>
#include <memory>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <vector>

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include "resource.h"
