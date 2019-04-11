#include "gameMenuItem.h"

gameMenuItem::gameMenuItem(char* text, char* p) :
  menuItem(text) {
  xbePath = (char*)malloc(strlen(p) * sizeof(char));
  strcpy(xbePath, p);
}

gameMenuItem::gameMenuItem(const char* text, const char* p) :
  gameMenuItem(const_cast<char*>(text), const_cast<char*>(p)) {}

gameMenuItem::~gameMenuItem() {
  free(xbePath);
}

char* gameMenuItem::getXBEPath() {
  return xbePath;
}

void gameMenuItem::setXBEPath(char* p) {
  xbePath = p;
}
