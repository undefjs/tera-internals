#include <node.h>
#include <windows.h>
//#include "../sdk.h"
#include "process.h"

using namespace v8;
using namespace node;

char *TERA_EXE = "TERA.exe";

int initGuard(char * szDLL) {
  int ret = injectDLL(TERA_EXE, szDLL);
  Sleep(2500);
  return ret;
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
