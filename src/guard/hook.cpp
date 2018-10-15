
#define GOBJECTS_PATTERN "\x00\x00\x00\x00\x6A\x01\x8B\x34\xB0\x8B\xCE\xE8\x00\x00\x00\x00"
#define GOBJECTS_MASK    "????xxxxxxxx????"
#define GOBJECTS_OFFSET  0x9

#define GNAMES_PATTERN   "\x00\x00\x00\x00\xFF\x75\x08\xC7\x45\x00\x00\x00\x00\x00\x8B\x0C\x91\xE8\x00\x00\x00\x00"
#define GNAMES_MASK     "????xxxxx?????xxxx????"
#define GNAMES_OFFSET    0x8

bool bDataCompare(const BYTE *pData, const BYTE *bMask, const char *szMask) {
  for (; *szMask; ++szMask, ++pData, ++bMask)
    if (*szMask == 'x' && *pData != *bMask)
      return false;
  return (*szMask) == NULL;
}

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask) {
  for (DWORD i = 0; i < dwLen; i++)
    if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
      return (DWORD)(dwAddress + i);
  return 0;
}

DWORD absAddr(DWORD rel1, DWORD rel2) {
  DWORD tmp1 = *((DWORD *)(rel1 + 1));
  DWORD tmp2 = rel1 + tmp1 + 5;
  DWORD tmp3 = tmp2 - rel2 - 5;
  return tmp3;
}
