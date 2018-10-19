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

  DWORD pS1Game = *(DWORD*)dwFindPattern((DWORD)me.modBaseAddr, me.modBaseSize, (BYTE*)S1GAME_PATTERN, S1GAME_MASK);
  if(pS1Game == NULL) return false;

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
  if(obj->Class && !obj->Outer) {
    return getName(obj->Name.Index);
  }

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

FN_RETURN fnGetFOV(json j) {
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

FN_RETURN fnSetFOV(json j) {
  FN_RETURN ret = { 0 };
  ret.error = true;

  auto camera = (AS1PlayerCamera*)findObject("S1PlayerCamera Start.TheWorld.PersistentLevel.S1PlayerCamera");
  auto pFnSetFOV = (UFunction*)findObject("Function Engine.Camera.SetFOV");

	ACamera_execSetFOV_Parms SetFOV_Parms;
	SetFOV_Parms.NewFOV = j["value"].get<float>();
  camera->ProcessEvent ( pFnSetFOV, &SetFOV_Parms, NULL );

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnSlow(json j) {
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

FN_RETURN fnFly(json j) {
  FN_RETURN ret = { 0 };
  ret.error = true;

  dumpObjects();

  auto playerController = (AS1PlayerController*)findObject("S1PlayerController Start.TheWorld.PersistentLevel.S1PlayerController");
  auto pFnEnableCheats = (UFunction*)findObject("Function Engine.PlayerController.EnableCheats");

	APlayerController_execEnableCheats_Parms EnableCheats_Parms;
	playerController->ProcessEvent(pFnEnableCheats, &EnableCheats_Parms, NULL);

	//---

  auto cheatManager = (UCheatManager*)findObject("CheatManager Start.TheWorld.PersistentLevel.S1PlayerController.CheatManager");
  auto pFnFly = (UFunction*)findObject("Function Engine.CheatManager.Fly");

	UCheatManager_execFly_Parms Fly_Parms;
	cheatManager->ProcessEvent(pFnFly, &Fly_Parms, NULL);

  playerController->bCheatFlying = true;

  //---

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnSpawn(json j) {
  FN_RETURN ret = { 0 };
  ret.error = true;

  //https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Actors/Spawning

  auto world = (UWorld*)findObject("World Start.TheWorld");
  //...

  //---

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnDumpObjects(json j) {
  FN_RETURN ret = { 0 };

  dumpObjects();

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnGetObject(json j) {
  FN_RETURN ret = { 0 };
  ret.error = true;

  auto str = j["name"].get<std::string>();
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  UObjectEx * obj = findObject(cstr);

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"address\": %d }", (DWORD)obj);

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}

FN_RETURN fnSetFPS(json j) {
  FN_RETURN ret = { 0 };
  ret.error = true;

  auto fps = j["value"].get<float>();

  auto gameEngine = (UGameEngine*)findObject("GameEngine Transient.GameEngine");
  gameEngine->bSmoothFrameRate = true;
  gameEngine->MinSmoothedFrameRate = fps;
  gameEngine->MaxSmoothedFrameRate = fps;

  char buffer[MAX_PATH];
  snprintf(buffer, MAX_PATH, "{ \"ok\": true }");

  ret.error = false;
  ret.buffer = buffer;
  return ret;
}
