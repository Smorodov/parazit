//////////////////////////////////////////////////////////////////////////////
//
//  Detours Test Program (tdll2x.cpp of talloc.exe/tdll2x.dll)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

//////////////////////////////////////////////////////////////////// DLL Stuff
//
__declspec(dllexport) unsigned long __stdcall Dll2Function(unsigned long Value)
{
	return Value + 1;
}

///////////////////////////////////////////////////////////////// End of File.
