#include "gameMenuItem.h"

gameMenuItem::gameMenuItem(char* text, char* p) :
  menuItem(text), xbePath(p) {}

char* gameMenuItem::getXBEPath() {
  return xbePath;
}

void gameMenuItem::setXBEPath(char* p) {
  xbePath = p;
}
