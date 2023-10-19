#include "windows.h"
#include <tchar.h>
#include <detours.h>
#include <iostream>

class Pipe
{
	private:

		HANDLE hChildStd_IN_Rd;
		HANDLE hChildStd_IN_Wr;

		HANDLE hChildStd_OUT_Rd;
		HANDLE hChildStd_OUT_Wr;

		HANDLE hChildStd_ERR_Rd;
		HANDLE hChildStd_ERR_Wr;

		PROCESS_INFORMATION piProcInfo;
		// PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;


	public:
		Pipe();
		~Pipe()
		{
			Close();
		}

		int Open(const char *cmdline,const char *injectedDLLname);
		int Close();
		size_t Read(char *buffer, size_t size);
		size_t Write(char *buffer, size_t size);
};
