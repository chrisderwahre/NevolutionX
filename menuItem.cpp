#include "menuItem.h"

const char* menuItem::getLabel() {
  return label;
}

void menuItem::setLabel(char* text) {
  label = text;
}
