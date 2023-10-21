//////////////////////////////////////////////////////////////////////////////
//
//  Detour Test Program (findfunc.cpp of findfunc.exe)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include <detours.h>
#include <stdio.h>
#include <windows.h>
// #include "target.h"

int __cdecl main(void)
{
    DWORD(WINAPI * Target)
    (DWORD) = NULL;
    printf("findfunc.exe: Starting.\n");
    fflush(stdout);
    printf("DLLs:\n");
    PVOID addr = NULL;
    LoadLibrary("target.dll");
    for (HMODULE hModule = NULL; (hModule = DetourEnumerateModules(hModule)) != NULL;) {
        CHAR szName[MAX_PATH] = { 0 };
        GetModuleFileNameA(hModule, szName, sizeof(szName) - 1);
        printf("  %p: %s\n", hModule, szName);
        addr = DetourFindFunction(
            szName,
            (LPCSTR) "Target");
        if (addr) {
            printf("Found!\n");
            break;
        }
    }

    if (!addr) {
        return 0;
    }

    DWORD dwCount = 10000;
    for (int i = 0; i < 3; i++) {
        printf("findfunc.exe: Calling (%d).\n", dwCount);
        Target = (DWORD(WINAPI*)(DWORD))addr;
        dwCount = Target(dwCount) + 10000;
    }
    return 0;
}
//
///////////////////////////////////////////////////////////////// End of File.
