#ifndef FINDXBE_H
#define FINDXBE_H

#include "vector.hpp"
#include "gameMenuItem.h"
#include "outputLine.h"

#ifdef NXDK
#include <hal/fileio.h>
#include <hal/xbox.h>
#include <stdio.h>
#endif

int findXBE(void* list);

#endif
