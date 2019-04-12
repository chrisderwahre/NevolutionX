#include "menuItem.h"

const char* menuItem::getLabel() {
  return label;
}

void menuItem::setLabel(char* text) {
  label = (char*)realloc(label, strlen(text) * sizeof(char));
  strcpy(label, text);
}
