#include <cstdio>
#include <windows.h>
#include "socket.h"

char * REPLY_ERROR = "{ \"error\": true }\0";

void onReceive(SOCKET s, char * buf, int len) {
  if((_stricmp(buf, "print") == 0)) {
    char buffer[MAX_PATH];
    snprintf(buffer, MAX_PATH, "{ \"error\": false, \"content\": %d }", len);
    socketSend(s, buffer, strlen(buffer));
  }
  else {
    socketSend(s, REPLY_ERROR, strlen(REPLY_ERROR));
  }
}

void setupServer() {
  socketListen(onReceive);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)setupServer, NULL, 0, NULL);
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
