#include <node.h>
#include <windows.h>
#include <tlhelp32.h>

#include "sdk.h"
#include "hook.cpp"
#include "process.cpp"

/*
___:00649F07 3B 35 D0 A1 64 02                       cmp     esi, ds:dword_264A1D0
___:00649F0D 7D 22                                   jge     short loc_649F31
___:00649F0F A1 CC A1 64 02                          mov     eax, ds:g_Objects
___:00649F14 6A 01                                   push    1
___:00649F16 8B 34 B0                                mov     esi, [eax+esi*4]

3B 35 ?? ?? ?? ?? 7D 22 A1 ?? ?? ?? ?? 6A 01 8B 34 B0

--

___:0069A184 8B 75 08                                mov     esi, [ebp+arg_0]
___:0069A187 57                                      push    edi
___:0069A188 8B F9                                   mov     edi, ecx
___:0069A18A 8B 0D 54 3D 60 02                       mov     ecx, ds:g_Names
___:0069A190 56                                      push    esi
___:0069A191 8B 07                                   mov     eax, [edi]
___:0069A193 8B 0C 81                                mov     ecx, [ecx+eax*4]

8B 75 08 57 8B F9 8B 0D ?? ?? ?? ?? 56 8B 07 8B 0C 81

*/

#define GOBJECTS_PATTERN "\x3B\x35\x00\x00\x00\x00\x7D\x22\xA1\x00\x00\x00\x00\x6A\x01\x8B\x34\xB0"
#define GOBJECTS_MASK    "xx????xxx????xxxxx"
#define GOBJECTS_OFFSET  0x9

#define GNAMES_PATTERN   "\x8B\x75\x08\x57\x8B\xF9\x8B\x0D\x00\x00\x00\x00\x56\x8B\x07\x8B\x0C\x81"
#define GNAMES_MASK     "xxxxxxxx????xxxxxx"
#define GNAMES_OFFSET    0x8

char *TERA_EXE = "TERA.exe";

DWORD pGObjects = NULL;
DWORD pGNames = NULL;
TArray<UObjectEx*> *GObjects = NULL;
TArray<FNameEntry*> *GNames = NULL;

using namespace v8;
using namespace node;

int get() {
  GObjects = NULL;
  GNames = NULL;

  DWORD pID = getPID(TERA_EXE);
  if(pID == 0) return 0;

  MODULEENTRY32 me = { 0 };
  getModule(pID, TERA_EXE, me);
  LPVOID teraBase = me.modBaseAddr;
  DWORD teraSize = me.modBaseSize;

  pGObjects = dwFindPattern((DWORD)teraBase, teraSize, (BYTE*)GOBJECTS_PATTERN, GOBJECTS_MASK) + GOBJECTS_OFFSET;
  if(pGObjects == NULL) return 1;

  pGNames = dwFindPattern((DWORD)teraBase, teraSize, (BYTE*)GNAMES_PATTERN, GNAMES_MASK) + GNAMES_OFFSET;
  if(pGNames == NULL) return 2;

  GObjects = (TArray<UObjectEx*>*)(*(DWORD*)pGObjects);
  GNames = (TArray<FNameEntry*>*)(*(DWORD*)pGNames);
  return 3;
}

void Get(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  int retCode = get();

  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "retCode"), Number::New(isolate, retCode));
  obj->Set(String::NewFromUtf8(isolate, "pGObjects"), Number::New(isolate, pGObjects));
  obj->Set(String::NewFromUtf8(isolate, "pGNames"), Number::New(isolate, pGNames));

  args.GetReturnValue().Set(obj);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "get", Get);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init);
