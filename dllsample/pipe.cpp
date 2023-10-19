#include "pipe.h"

Pipe::Pipe()
{
	hChildStd_IN_Rd = NULL;
	hChildStd_IN_Wr = NULL;
	hChildStd_OUT_Rd = NULL;
	hChildStd_OUT_Wr = NULL;
	hChildStd_ERR_Rd = NULL;
	hChildStd_ERR_Wr = NULL;
}

int
Pipe::Open(const char* cmdLine,const char* injectedDLLname)
{
	SECURITY_ATTRIBUTES saAttr;	
	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	// Create a pipe for the child process's STDOUT.
	if (!CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0))
	{
		std::cout << TEXT("StdoutRd CreatePipe") << std::endl;
	}
	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
	{
		std::cout << TEXT("Stdout SetHandleInformation") << std::endl;
	}
	// Create a pipe for the child process's STDIN.
	if (!CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0))
	{
		std::cout << TEXT("Stdin CreatePipe") << std::endl;
	}
	// Ensure the write handle to the pipe for STDIN is not inherited.
	if (!SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
	{
		std::cout << TEXT("Stdin SetHandleInformation") << std::endl;
	}
	// Create the child process.
	BOOL bSuccess = FALSE;
	// Set up members of the PROCESS_INFORMATION structure.
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
	// Set up members of the STARTUPINFO structure.
	// This structure specifies the STDIN and STDOUT handles for redirection.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = hChildStd_OUT_Wr;
	siStartInfo.hStdInput = hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	// Create the child process.
	bSuccess =
	    DetourCreateProcessWithDll(NULL,
	                               (LPSTR)cmdLine, // command line
	                               NULL,           // process security attributes
	                               NULL, // primary thread security attributes
	                               TRUE, // handles are inherited
	                               0,    // creation flags
	                               NULL, // use parent's environment
	                               NULL, // use parent's current directory
	                               &siStartInfo, // STARTUPINFO pointer
	                               &piProcInfo,  // receives PROCESS_INFORMATION
	                               injectedDLLname,
	                               NULL);
	if (!bSuccess)
	{
		std::cout << TEXT("CreateProcess") << std::endl;
	}
	else
	{
		// Close handles to the child process and its primary thread.
		// Some applications might keep these handles to monitor the status
		// of the child process, for example.
		if (piProcInfo.hProcess)
		{
			CloseHandle(piProcInfo.hProcess);
			piProcInfo.hProcess = NULL;
		}
		if (piProcInfo.hThread)
		{
			CloseHandle(piProcInfo.hThread);
			piProcInfo.hThread = NULL;
		}
		// Close handles to the stdin and stdout pipes no longer needed by the
		// child process. If they are not explicitly closed, there is no way to
		// recognize that the child process has ended.
		CloseHandle(hChildStd_OUT_Wr);
		hChildStd_OUT_Wr = NULL;
		CloseHandle(hChildStd_IN_Rd);
		hChildStd_IN_Rd = NULL;
	}
	return 0;
}

int
Pipe::Close()
{
	if (hChildStd_IN_Rd != NULL)
	{
		CloseHandle(hChildStd_IN_Rd);
		hChildStd_IN_Rd = NULL;
	}
	if (hChildStd_IN_Wr != NULL)
	{
		CloseHandle(hChildStd_IN_Wr);
		hChildStd_IN_Wr = NULL;
	}
	if (hChildStd_OUT_Rd != NULL)
	{
		CloseHandle(hChildStd_OUT_Rd);
		hChildStd_OUT_Rd = NULL;
	}
	if (hChildStd_OUT_Wr != NULL)
	{
		CloseHandle(hChildStd_OUT_Wr);
		hChildStd_OUT_Wr = NULL;
	}
	if (hChildStd_ERR_Rd != NULL)
	{
		CloseHandle(hChildStd_ERR_Rd);
		hChildStd_ERR_Rd = NULL;
	}
	if (hChildStd_ERR_Wr != NULL)
	{
		CloseHandle(hChildStd_ERR_Wr);
		hChildStd_ERR_Wr = NULL;
	}
	if (piProcInfo.hProcess)
	{
		CloseHandle(piProcInfo.hProcess);
	}
	if (piProcInfo.hThread)
	{
		CloseHandle(piProcInfo.hThread);
	}
	return 0;
}
size_t
Pipe::Read(char* buffer, size_t size)
{
	// check if the process terminated
	DWORD dwRead;
	BOOL bSuccess = ReadFile(hChildStd_OUT_Rd, buffer, size, &dwRead, NULL);
	return bSuccess ? dwRead : 0;
}
size_t
Pipe::Write(char* buffer, size_t size)
{
	DWORD dwWritten;
	BOOL bSuccess = WriteFile(hChildStd_IN_Wr, buffer, size, &dwWritten, NULL);
	return bSuccess ? dwWritten : 0;
}

/*
int main()
{
    Pipe pipe;
    pipe.Open("pipe_client.exe");

   char buf[16384];
   memset(buf,0,16384);
   sprintf(buf,"1+1\n");
   pipe.Write(buf, sizeof(buf));

    //while (1)
    {
    char buf[16384];
    memset(buf,0,16384);
    size_t res = 0;
    do
    {
        res = pipe.Read(buf, sizeof(buf));
        std::cout << buf ;
    } while (res != 0);
    }
    pipe.Close();
    return 0;
}
*/
