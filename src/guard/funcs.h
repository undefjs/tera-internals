struct FN_RETURN {
  bool error;
  char * buffer;
};

char * getName(int);
char * getNameByAddr(DWORD);
char * getFullNameByAddr(DWORD);
bool InitEngine();

#include "include/json.hpp"
using json = nlohmann::json;

FN_RETURN fnGetFOV(json);
FN_RETURN fnSetFOV(json);
FN_RETURN fnSlow(json);
FN_RETURN fnFly(json);
FN_RETURN fnSpawn(json);
FN_RETURN fnDumpObjects(json);
FN_RETURN fnGetObject(json);
FN_RETURN fnSetFPS(json);
FN_RETURN fnGetPlayer(json);
FN_RETURN fnHideActor(json);
FN_RETURN fnFreeCam(json);
