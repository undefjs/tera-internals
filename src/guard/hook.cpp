#include <windows.h>
#include <tlhelp32.h>
#include "hook.h"

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

bool bDataCompare(const BYTE *pData, const BYTE *bMask, const char *szMask) {
  for (; *szMask; ++szMask, ++pData, ++bMask)
    if (*szMask == 'x' && *pData != *bMask)
      return false;
  return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask) {
  for (DWORD i = 0; i < dwLen; i++)
    if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
      return (DWORD)(dwAddress + i);
  return 0;
}
