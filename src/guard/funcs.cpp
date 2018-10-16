#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include "hook.h"
#include "funcs.h"
#include "../sdk.h"

char * TERA_EXE = "TERA.exe";

TArray<UObjectEx*> *GObjects = NULL;
TArray<FNameEntry*> *GNames = NULL;

bool InitEngine() {
  MODULEENTRY32 me = { 0 };
  if(!getModule(GetCurrentProcessId(), TERA_EXE, me)) return false;

  DWORD pGObjects = *(DWORD*)dwFindPattern((DWORD)me.modBaseAddr, me.modBaseSize, (BYTE*)GOBJECTS_PATTERN, GOBJECTS_MASK);
  if(pGObjects == NULL) return false;

  DWORD pGNames = *(DWORD*)dwFindPattern((DWORD)me.modBaseAddr, me.modBaseSize, (BYTE*)GNAMES_PATTERN, GNAMES_MASK);
  if(pGNames == NULL) return false;

  GObjects = (TArray<UObjectEx*>*)pGObjects;
  GNames = (TArray<FNameEntry*>*)pGNames;
  return true;
}

//---------------------

char * getName(int idx) {
  if(idx >= 0 && idx <= GNames->Count) {
    return GNames->Data[idx]->Name;
  }
  return "(null)";
};

char * getFullName(UObjectEx *obj) {
  if (obj->Class && obj->Outer) {
    static char cOutBuffer[512];
    char cTmpBuffer[512];

    strcpy_s(cOutBuffer, getName(obj->Name.Index));

    for (UObjectEx* pOuter = obj->Outer; pOuter; pOuter = pOuter->Outer)
    {
      strcpy_s(cTmpBuffer, getName(pOuter->Name.Index));
      strcat_s(cTmpBuffer, ".");

      size_t len1 = strlen(cTmpBuffer);
      size_t len2 = strlen(cOutBuffer);

      memmove(cOutBuffer + len1, cOutBuffer, len1 + len2 + 1);
      memcpy(cOutBuffer, cTmpBuffer, len1);
    }

    UObjectEx* cls = (UObjectEx*)obj->Class;
    strcpy_s(cTmpBuffer, getName(cls->Name.Index));
    strcat_s(cTmpBuffer, " ");

    size_t len1 = strlen(cTmpBuffer);
    size_t len2 = strlen(cOutBuffer);

    memmove(cOutBuffer + len1, cOutBuffer, len1 + len2 + 1);
    memcpy(cOutBuffer, cTmpBuffer, len1);

    return cOutBuffer;
  }

  return "(null)";
}

UObjectEx * findObject(char *name) {
  for (int i = 0; i < GObjects->Count; i++) {
    if (!GObjects->Data[i]) { continue; }

    UObjectEx *obj = GObjects->Data[i];
    if (_stricmp(getFullName(obj), name) == 0)
      return obj;
  }

  return NULL;
}

void dumpObjects() {
  FILE *fp = NULL;
  fopen_s(&fp, "objdump.txt", "w");

  for (int i = 0; i < GObjects->Count; i++) {
    if (!GObjects->Data[i]) { continue; }

    UObjectEx *obj = GObjects->Data[i];
    fprintf(fp, "[%06i:%06i] %-50s 0x%X\n", i, obj->Name.Index, getFullName(obj), (DWORD)GObjects->Data[i]);
  }

  fclose(fp);
}

FN_RETURN fnGetFOV() {
  FN_RETURN ret = { 0 };
  ret.error = true;

  auto camera = (AS1PlayerCamera*)findObject("S1PlayerCamera Start.TheWorld.PersistentLevel.S1PlayerCamera");
  auto pFnGetFOVAngle = (UFunction*)findObject("Function Engine.Camera.GetFOVAngle");

  ACamera_execGetFOVAngle_Parms GetFOVAngle_Parms;
  camera->ProcessEvent(pFnGetFOVAngle, &GetFOVAngle_Parms, NULL);

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"FOV\": %.2f }", GetFOVAngle_Parms.ReturnValue);

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnSlow() {
  FN_RETURN ret = { 0 };
  ret.error = true;

  auto cheatManager = (UCheatManager*)findObject("CheatManager Start.TheWorld.PersistentLevel.S1PlayerController.CheatManager");
  auto pFnSloMo = (UFunction*)findObject("Function Engine.CheatManager.SloMo");

	UCheatManager_execSloMo_Parms SloMo_Parms;
	SloMo_Parms.T = 0.25f;

	cheatManager->ProcessEvent(pFnSloMo, &SloMo_Parms, NULL);

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}
