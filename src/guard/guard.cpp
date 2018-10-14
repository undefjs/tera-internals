#include <windows.h>

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    MessageBoxA(0, "hi :)", 0, 0);
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }

  return TRUE;
}
