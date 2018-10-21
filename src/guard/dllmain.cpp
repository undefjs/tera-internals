#include <cstdio>
#include <windows.h>
#include "socket.h"
#include "funcs.h"

#include "include/json.hpp" //https://github.com/nlohmann/json
using json = nlohmann::json;

typedef FN_RETURN (*pFunc)(json j);
std::map<std::string, pFunc> FUNC_MAP {
  { "getfov", fnGetFOV },
  { "setfov", fnSetFOV },
  { "slowmo", fnSlow },
  { "fly", fnFly },
  { "spawn", fnSpawn },
  { "dump", fnDumpObjects },
  { "get", fnGetObject },
  { "setfps", fnSetFPS },
  { "getplayer", fnGetPlayer },
  { "hide", fnHideActor },
  { "cam", fnFreeCam }
};

char * REPLY_ERROR = R"({ "error": true, "reason": "%s." })";
char * REPLY_SUCCESS = R"({ "error": false, "content": %s })";

std::string recvBuffer;
std::string recvDelimiter = "\n";

void onReceive(SOCKET s, char * buf, int len) {
  recvBuffer += std::string(buf);

  size_t pos = 0;
  while((pos = recvBuffer.find(recvDelimiter)) != std::string::npos) {
    std::string token = recvBuffer.substr(0, pos);
    recvBuffer.erase(0, pos + recvDelimiter.length());

    char sendBuffer[MAX_PATH];

    json j = json::parse(token, nullptr, false);
    if(j.is_discarded()) {
      snprintf(sendBuffer, MAX_PATH, REPLY_ERROR, "Bad JSON request");
      socketSend(s, sendBuffer, strlen(sendBuffer));
      continue;
    }

    pFunc fn = FUNC_MAP[j["cmd"].get<std::string>()];
    if(fn == NULL) {
      snprintf(sendBuffer, MAX_PATH, REPLY_ERROR, "Unknown command");
      socketSend(s, sendBuffer, strlen(sendBuffer));
      continue;
    }

    FN_RETURN ret = (*fn)(j);
    snprintf(sendBuffer, MAX_PATH, REPLY_SUCCESS, ret.buffer);
    socketSend(s, sendBuffer, strlen(sendBuffer));
  }

}

void setupServer() {
  socketListen(onReceive);
}

#define PROCESS_EVENT 0x00722EE0

char dbgBuffer[MAX_PATH];
DWORD patchReturn;

DWORD pMyThis = NULL;
DWORD pMyFunc = NULL;
char * szThis;
char * szFunc;

void __declspec(naked) hProcessEvent() {
  __asm {
    mov [pMyThis], ecx
    push [esp + 4]
    pop [pMyFunc]
    pushad
  }

  szThis = getFullNameByAddr(pMyThis);
  szFunc = getNameByAddr(pMyFunc);

  //snprintf(dbgBuffer, MAX_PATH, "ProcessEvent %08X->%08X", pMyThis, pMyFunc);
  snprintf(dbgBuffer, MAX_PATH, "ProcessEvent %s->%s()", szThis, szFunc);
  OutputDebugStringA(dbgBuffer);

  __asm {
    popad
    push ebp
    mov ebp, esp
    push 0xFF
    jmp patchReturn
  }
}

void hookPE() {
  *((BYTE *)(PROCESS_EVENT)) = 0xE9; //JMP
  *((DWORD *)(PROCESS_EVENT + 1)) = (DWORD)&hProcessEvent - PROCESS_EVENT - 5;
  patchReturn = PROCESS_EVENT + 5;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    if(!InitEngine()) return FALSE;
    //hookPE();
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)setupServer, NULL, 0, NULL);
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
