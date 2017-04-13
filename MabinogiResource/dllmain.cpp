// dllmain.cpp : Defines the entry point for the DLL application.

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

static HINSTANCE g_hInst = 0;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    BOOL rc = TRUE;
    switch (fdwReason)
    {
    // 正しく処理が終わった場合はTRUEを返す必要あり
    case DLL_PROCESS_ATTACH:
        g_hInst = hinstDLL;
        break;
    case DLL_PROCESS_DETACH:
        g_hInst = 0;
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return rc;
}