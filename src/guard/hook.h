#include <tlhelp32.h>

#define GOBJECTS_PATTERN "\x00\x00\x00\x00\x6A\x01\x8B\x34\xB0\x8B\xCE\xE8\x00\x00\x00\x00"
#define GOBJECTS_MASK    "????xxxxxxxx????"

#define GNAMES_PATTERN   "\x00\x00\x00\x00\xFF\x75\x08\xC7\x45\x00\x00\x00\x00\x00\x8B\x0C\x91\xE8\x00\x00\x00\x00"
#define GNAMES_MASK      "????xxxxx?????xxxx????"

#define S1GAME_PATTERN   "\x00\x00\x00\x00\x56\x8B\xF1\x8B\x48\x14\x8B\x01\xFF\x50\x18\x83\xEC\x0C\x8B\xCC"
#define S1GAME_MASK      "????xxxxxxxxxxxxxxxx"

BOOL getModule(DWORD, char *, MODULEENTRY32 &);
DWORD dwFindPattern(DWORD, DWORD, BYTE *, char *);
