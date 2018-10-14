#include <windows.h>

void pipeHello() {
  HANDLE hPipe = CreateFile("\\\\.\\pipe\\TeraGuard", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  if(hPipe == INVALID_HANDLE_VALUE) return;

  DWORD dwWritten = NULL;
  WriteFile(hPipe, "Hello Pipe\n", 12, &dwWritten, NULL);

  CloseHandle(hPipe);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    //MessageBoxA(0, "hi :)", 0, 0);
    //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pipeHello, NULL, 0, NULL);
    pipeHello();
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }

  return TRUE;
}
