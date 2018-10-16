#include <cstdio>
#include <windows.h>
#include "socket.h"
#include "funcs.h"

#include "include/json.hpp" //https://github.com/nlohmann/json
using json = nlohmann::json;

char * REPLY_ERROR = R"({ "error": true })";
char * REPLY_SUCCESS = R"({ "error": false, "content": %s })";

void onReceive(SOCKET s, char * buf, int len) {
  char buffer[MAX_PATH];

  std::string str = std::string(buf);
  auto j = json::parse(str);
  auto cmd = j["cmd"];

  if(cmd == "get") {
    FN_RETURN ret = fnGetFOV();
    snprintf(buffer, MAX_PATH, REPLY_SUCCESS, ret.buffer);
    socketSend(s, buffer, strlen(buffer));
  }
  else if(cmd == "slow") {
    FN_RETURN ret = fnSlow();
    snprintf(buffer, MAX_PATH, REPLY_SUCCESS, ret.buffer);
    socketSend(s, buffer, strlen(buffer));
  }
  else if(cmd == "fly") {
    FN_RETURN ret = fnFly();
    snprintf(buffer, MAX_PATH, REPLY_SUCCESS, ret.buffer);
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
    if(!InitEngine()) return FALSE;
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)setupServer, NULL, 0, NULL);
    break;
  }
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
