#ifndef OUTPUTLINE_H
#define OUTPUTLINE_H

#ifdef NXDK
#include <xboxrt/debug.h>
#include "stdio.h"
#else
#include <SDL.h>
#endif

#include "stdarg.h"

void outputLine(char* format, ...);

#endif // OUTPUTLINE_H
