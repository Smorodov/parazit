//////////////////////////////////////////////////////////////////////////////
//
//  Detours Test Program (tdll4x.cpp of talloc.exe/tdll4x.dll)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

//////////////////////////////////////////////////////////////////// DLL Stuff
//
__declspec(dllexport) unsigned long __stdcall Dll4Function(unsigned long Value)
{
	return Value + 1;
}

///////////////////////////////////////////////////////////////// End of File.
