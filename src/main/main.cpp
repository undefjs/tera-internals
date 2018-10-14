#include <node.h>
#include <windows.h>
#include <tlhelp32.h>

#include "../sdk.h"
//#include "hook.cpp"
#include "process.cpp"

#define GOBJECTS_PATTERN "\x00\x00\x00\x00\x6A\x01\x8B\x34\xB0\x8B\xCE\xE8\x00\x00\x00\x00"
#define GOBJECTS_MASK    "????xxxxxxxx????"
#define GOBJECTS_OFFSET  0x9

#define GNAMES_PATTERN   "\x00\x00\x00\x00\xFF\x75\x08\xC7\x45\x00\x00\x00\x00\x00\x8B\x0C\x91\xE8\x00\x00\x00\x00"
#define GNAMES_MASK     "????xxxxx?????xxxx????"
#define GNAMES_OFFSET    0x8

char *TERA_EXE = "TERA.exe";
char *GUARD_DLL = "teraguard32.dll";

using namespace v8;
using namespace node;

char * szModulePath;

void initPipe() {
  // https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows

  char buffer[1024] = { 0 };
  HANDLE hPipe = CreateNamedPipe(
    "\\\\.\\pipe\\TeraGuard",
    PIPE_ACCESS_DUPLEX,
    PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
    1,
    1024 * 16,
    1024 * 16,
    NMPWAIT_USE_DEFAULT_WAIT,
    NULL
  );

  while(hPipe != INVALID_HANDLE_VALUE) {
    if(ConnectNamedPipe(hPipe, NULL) != FALSE) {
      DWORD dwRead = NULL;
      while(ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE) {
        buffer[dwRead] = '\0';
        MessageBoxA(0, buffer, 0, 0);
      }
    }

    DisconnectNamedPipe(hPipe);
  }

}

int pipeHello() {
  HANDLE hPipe = CreateFile("\\\\.\\pipe\\TeraGuard", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  if(hPipe == INVALID_HANDLE_VALUE) return 0;

  DWORD dwWritten = NULL;
  WriteFile(hPipe, "Hello Pipe\n", 12, &dwWritten, NULL);

  CloseHandle(hPipe);
  return 1;
}

int initGuard(char * szDLL) {
  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initPipe, NULL, 0, NULL);
  Sleep(5000);
  return pipeHello();
  //return injectDLL(TERA_EXE, szDLL);
}

void InitGuard(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if(args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if(!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  Local<String> str = Local<String>::Cast(args[0]);
  String::Utf8Value value(str);

  int ret = initGuard(*value);
  args.GetReturnValue().Set(Number::New(isolate, ret));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "initGuard", InitGuard);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init);
