struct FN_RETURN {
  bool error;
  char * buffer;
};

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
