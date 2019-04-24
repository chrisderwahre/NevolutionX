#include "findXBE.h"

int findXBE(void* list) {
  vector<gameMenuItem>* gmi_list = static_cast<vector<gameMenuItem>*>(list);
  char* path = const_cast<char*>("C:\\");
  char* mask = const_cast<char*>("*");
#ifdef NXDK
  int ret;
  char tmp[64];
  FILE* tmpFILE = nullptr;
  fileData fData;
  HANDLE fHandle = openFolder(path);
  if (fHandle == nullptr) {
    return -1;
  }

  while (readFolder(fHandle, &fData) == STATUS_SUCCESS) {
    if (fData.f_Attributes & FILE_ATTRIBUTE_DIRECTORY) {
      tmp[0] = '\0';
      sprintf(tmp, "%s%s\\default.xbe", path, fData.f_FileName);
      tmpFILE = fopen(tmp, "rb");
      if (tmpFILE != nullptr) {
        gmi_list->push_back(gameMenuItem(fData.f_FileName, tmp));
        fclose(tmpFILE);
        tmpFILE = nullptr;
      }
    }
  }
  free(tmp);
  closeFolder(fHandle);
#else
  for (int i = 0; i < 7; ++i) {
    gmi_list->push_back(gameMenuItem(path, mask));
  }
#endif
  return 0;
}