// @author: https://github.com/caali-hackerman

#define NOMINMAX
#include <Windows.h>
#include <string>

bool injectDLL(DWORD dwProcessId, LPCWSTR lpszDLLPath)
{
  HANDLE  hProcess, hThread;
  LPVOID  lpBaseAddr, lpFuncAddr;
  BOOL    bSuccess = FALSE;

  if ((hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | THREAD_QUERY_INFORMATION, FALSE, dwProcessId)))
  {
    DWORD dwMemSize = sizeof(WCHAR)*(lstrlenW(lpszDLLPath) + 1);
    if ((lpBaseAddr = VirtualAllocEx(hProcess, NULL, dwMemSize, MEM_COMMIT, PAGE_READWRITE)))
    {
      if (WriteProcessMemory(hProcess, lpBaseAddr, lpszDLLPath, dwMemSize, NULL))
      {
        HMODULE hUserDLL = LoadLibrary(TEXT("kernel32.dll"));
        if (hUserDLL == NULL)
          hUserDLL = LoadLibrary(TEXT("kernelbase.dll"));

        if (hUserDLL)
        {
          if ((lpFuncAddr = GetProcAddress(hUserDLL, "LoadLibraryW")))
          {
            if ((hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpFuncAddr, lpBaseAddr, 0, NULL)))
            {
              WaitForSingleObject(hThread, INFINITE);

              DWORD dwExitCode;
              if (GetExitCodeThread(hThread, &dwExitCode))
                bSuccess = (dwExitCode != 0) ? TRUE : FALSE;
              CloseHandle(hThread);
            }
          }
          FreeLibrary(hUserDLL);
        }
      }
      VirtualFreeEx(hProcess, lpBaseAddr, 0, MEM_RELEASE);
    }
    CloseHandle(hProcess);
  }

  return bSuccess == TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  int argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

  if (argc < 3)
    return 1;

  return injectDLL(std::stoul(argv[1]), argv[2]) ? 0 : 1;
}
