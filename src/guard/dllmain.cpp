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
  { "get", fnGetObject }
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

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    if(!InitEngine()) return FALSE;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)setupServer, NULL, 0, NULL);
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
