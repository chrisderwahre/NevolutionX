#include "findXBE.h"

int findXBE(void* list) {
  vector<gameMenuItem>* gmi_list = static_cast<vector<gameMenuItem>*>(list);
  char* path = const_cast<char*>("C:\\");
  char* mask = const_cast<char*>("*");
#ifdef NXDK
  int ret;
  char tmp[64];
  FILE* tmpFILE = nullptr;
  XBOX_FIND_DATA fData;
  // FIXME: Should not have to be casted!
  HANDLE fHandle = (HANDLE)XFindFirstFile(path, mask, &fData);
  // FIXME: Should not have to be casted!
  if (fHandle == (HANDLE)INVALID_HANDLE_VALUE) {
    return -1;
  } else {
    ret = STATUS_SUCCESS;
  }

  while (ret == STATUS_SUCCESS) {
    if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      tmp[0] = '\0';
      sprintf(tmp, "%s%s\\default.xbe", path, fData.cFileName);
      tmpFILE = fopen(tmp, "rb");
      if (tmpFILE != nullptr) {
        gmi_list->push_back(gameMenuItem(fData.cFileName, tmp));
        fclose(tmpFILE);
        tmpFILE = nullptr;
      }
    }
    // FIXME: Should not have to be casted!
    ret = XFindNextFile((unsigned int)fHandle, &fData);
  }
  free(tmp);
  // FIXME: Should not have to be casted!
  XFindClose((unsigned int)fHandle);
#else
  for (int i = 0; i < 7; ++i) {
    gmi_list->push_back(gameMenuItem(path, mask));
  }
#endif
  return 0;
}
