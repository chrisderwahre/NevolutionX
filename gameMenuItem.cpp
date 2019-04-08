#include "gameMenuItem.h"

gameMenuItem::gameMenuItem(char* text, char* p, menuItem* prev, menuItem* next) :
  menuItem(text, prev, next) xbePath(p) {}

char* gameMenuItem::getXBEPath() {
  return xbePath;
}

void gameMenuItem::setXBEPath(char* p) {
  xbePath = p;
}
