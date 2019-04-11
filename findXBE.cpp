#include "findXBE.h"

int findXBE(void* list) {
  vector<gameMenuItem*>* gmi_list = static_cast<vector<gameMenuItem*>*>(list);
  char* path = const_cast<char*>("C:\\");
  char* mask = const_cast<char*>("*");
#ifdef NXDK
  int ret;
  char tmp[64];
  FILE* tmpFILE = nullptr;
  XBOX_FIND_DATA fData;
  unsigned int fHandle = XFindFirstFile(path, mask, &fData);
  if (fHandle == INVALID_HANDLE_VALUE) {
    return -1;
  } else {
    ret = STATUS_SUCCESS;
  }

  while (ret == STATUS_SUCCESS) {
    if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      tmp[0] = '\0';
      strcat(tmp, path);
      strcat(tmp, fData.cFileName);
      strcat(tmp, "\\default.xbe");
      tmpFILE = fopen(tmp, "rb");
      if (tmpFILE != nullptr) {
        gmi_list->push_back(new gameMenuItem(fData.cFileName, tmp));
        fclose(tmpFILE);
        tmpFILE = nullptr;
      }
    }
    ret = XFindNextFile(fHandle, &fData);
  }
  free(tmp);
  XFindClose(fHandle);
#else
  for (int i = 0; i < 7; ++i) {
    gmi_list->push_back(new gameMenuItem(path, mask));
  }
#endif
  return 0;
}
