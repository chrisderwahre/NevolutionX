#include "gameMenuItem.h"

gameMenuItem::gameMenuItem(char* text, char* p) :
  menuItem(text) {
  xbePath = (char*)malloc(strlen(p) * sizeof(char));
  strcpy(xbePath, p);
}

gameMenuItem::gameMenuItem(const char* text, const char* p) :
  menuItem(text), xbePath(const_cast<char*>(p)) {}

char* gameMenuItem::getXBEPath() {
  return xbePath;
}

void gameMenuItem::setXBEPath(char* p) {
  xbePath = p;
}
