#include "findXBE.h"

int findXBE(void* list) {
  vector<gameMenuItem*>* gmi_list = static_cast<vector<gameMenuItem*>*>(list);
  char* path = const_cast<char*>("C:\\");
  char* mask = const_cast<char*>("*");
#ifdef NXDK
  bool running;
  int ret;
  char tmp[64];
  FILE* tmpFILE = nullptr;
  XBOX_FIND_DATA fData;
  size_t fHandle = XFindFirstFile(path, mask, &fData);
  if (fHandle == INVALID_HANDLE_VALUE) {
    XSleep(2000);
    return -1;
  } else {
    running = true;
    if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      tmp[0] = '\0';
      strcat(strcat(strcat(tmp, path), fData.cFileName), "\\default.xbe");
      tmpFILE = fopen(tmp, "r");
      if (tmpFILE != nullptr) {
        gmi_list->push_back(new gameMenuItem(fData.cFileName, tmp));
        fclose(tmpFILE);
        tmpFILE = nullptr;
      }
    }
  }

  while (running) {
    ret = XFindNextFile(fHandle, &fData);
    if (ret == ERROR_NO_MORE_FILES) {
      running = false;
      continue;
    } else if (ret == STATUS_SUCCESS) {
      if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { 
        tmp[0] = '\0';
        strcat(strcat(strcat(tmp, path), fData.cFileName), "\\default.xbe");
        tmpFILE = fopen(tmp, "r");
        if (tmpFILE != nullptr) {
          gmi_list->push_back(new gameMenuItem(fData.cFileName, tmp));
          fclose(tmpFILE);
          tmpFILE = nullptr;
        }
      }
    }
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
