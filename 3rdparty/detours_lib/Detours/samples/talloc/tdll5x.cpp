//////////////////////////////////////////////////////////////////////////////
//
//  Detours Test Program (tdll5x.cpp of talloc.exe/tdll5x.dll)
//
//  Microsoft Research Detours Package
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

//////////////////////////////////////////////////////////////////// DLL Stuff
//
__declspec(dllexport) unsigned long __stdcall Dll5Function(unsigned long Value)
{
	return Value + 1;
}

///////////////////////////////////////////////////////////////// End of File.
