#include "pch.h"

BOOL APIENTRY DllMain( HMODULE module,
                       DWORD  ul_reason_for_call,
                       LPVOID resv
                     )
{
    (void) module;
    (void) resv;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

