//////////////////////////////////////////////////////////////////////////////
//
//  Detours Test Program (tdll9x.cpp of talloc.exe/tdll9x.dll)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

//////////////////////////////////////////////////////////////////// DLL Stuff
//
__declspec(dllexport) unsigned long __stdcall Dll9Function(unsigned long Value)
{
	return Value + 1;
}

///////////////////////////////////////////////////////////////// End of File.