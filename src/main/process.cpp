#include <windows.h>
#include <tlhelp32.h>

DWORD getPID(char *szName) {
  DWORD pID = 0;
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  PROCESSENTRY32 pe = { sizeof(pe) };
  if(Process32First(hSnapshot, &pe)) {
    do {
      if(_stricmp(pe.szExeFile, szName) == 0) {
        pID = pe.th32ProcessID;
        break;
      }
    }
    while(Process32Next(hSnapshot, &pe));
  }

  CloseHandle(hSnapshot);
  return pID;
}

BOOL getModule(DWORD dwPID, char *szName, MODULEENTRY32 &module) {
  BOOL ret = false;
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);

  MODULEENTRY32 me = { sizeof(me) };
  if (Module32First(hSnapshot, &me)) {
    do {
      if (_stricmp(me.szModule, szName) == 0) {
        ret = true;
        module = me;
        break;
      }
    } while (Module32Next(hSnapshot, &me));
  }

  CloseHandle(hSnapshot);
  return ret;
}

int injectDLL(char *szProcess, char *szDLL) {
  unsigned int pID = (unsigned int)getPID(szProcess);
  if(!pID) return 0;

  void * hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);
  if(!hProcess) return 1;

  unsigned int len = strlen(szDLL) + 1;
  void * pName = VirtualAllocEx(hProcess, nullptr, len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if(!pName) return 2;

  unsigned int bStatus = WriteProcessMemory(hProcess, pName, szDLL, len, nullptr);
  if(!bStatus) return 3;

  //TODO: hardcoded addresses
  //void * hKernel = (void *)0x777C0000;
  void * pLoadLibrary = (void *)(0x777C0000 + 0x000157B0);

/*
  - TODO: need fix, this will get 64 bits version of LoadLibraryA..
  - TODO: https://stackoverflow.com/questions/8776437/c-injecting-32-bit-targets-from-64-bit-process
  void * hKernel = GetModuleHandle("kernel32.dll");
  void * pLoadLibrary = GetProcAddress(hKernel, "LoadLibraryA");
  if(!pLoadLibrary) return 4;
*/

  void * hThreadId = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pName, 0, 0);
  if(!hThreadId) return 5;

  WaitForSingleObject(hThreadId, INFINITE);

  VirtualFreeEx(hProcess, pName, len, MEM_RELEASE);
  CloseHandle(hProcess);
  return 6;
}
