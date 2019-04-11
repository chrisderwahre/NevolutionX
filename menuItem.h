#ifndef MENUITEM_H
#define MENUITEM_H

#include <stdlib.h>
#include <string.h>

#include "outputLine.h"

class menuItem {
private:
  char* label;
public:
  menuItem(char* text) {
    label = (char*)malloc(strlen(text) * sizeof(char));
    strcpy(label, text);
  }
  menuItem(const char* text) : menuItem(const_cast<char*>(text)) {}
  const char* getLabel();
  void setLabel(char* text);
};
#endif
