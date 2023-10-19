#include <stdio.h>
#include <Windows.h>
#include <detours.h>

static auto real_Beep = ::Beep;
static auto real_fopen = ::fopen;
//-------------------------------------------------------------------------
static BOOL WINAPI my_Beep(DWORD dwFreq, DWORD dwDuration)
{
	printf("Beep(%u, %u)\n", dwFreq, dwDuration);
	return real_Beep(dwFreq, dwDuration);
}

static FILE* __cdecl my_fopen(_In_z_ char const* _FileName,
                              _In_z_ char const* _Mode)
{
	printf("fopen(%s,%s)\n", _FileName, _Mode);
	return real_fopen(_FileName,_Mode);
}

//-------------------------------------------------------------------------
int main()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)real_Beep, my_Beep);
	DetourAttach(&(PVOID&)real_fopen, my_fopen);
	auto error = DetourTransactionCommit();
	::Beep(200, 1000);
	::fopen("txt.txt", "w+");
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)real_Beep, my_Beep);
	error = DetourTransactionCommit();
	return 0;
}