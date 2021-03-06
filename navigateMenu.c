#include "navigateMenu.h"

#ifdef NXDK
const extern int SCREEN_WIDTH;
const extern int SCREEN_HEIGHT;
#else
int  SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
#endif

int menuLoop() {
  int i, done, currItem = 0;
  const char *driver;
  Uint32 windowFlags,renderFlags;
  SDL_Window *window;
  SDL_Renderer *renderer;
  int window_width, window_height;
  SDL_Event event;
  TTF_Font *font;
  menuItemList menuItems = mil_createNew();
  menuItemList *currList = &menuItems;

  mil_append_c(currList, "Games");
  mil_append_c(currList, "Launch DVD");
  mil_append_c(currList, "Applications");
  mil_append_c(currList, "Settings");
  
#ifdef NXDK
  windowFlags = SDL_WINDOW_SHOWN;
  renderFlags = 0;
#else
  windowFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE;
  renderFlags = SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED;
#endif

  window = SDL_CreateWindow("NevolutionX",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
  if (window == NULL) {
    outputLine("Window creation error: %s", SDL_GetError());
    thrd_exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, renderFlags);
  if (renderer == NULL) {
    outputLine("Renderer creation error: %s", SDL_GetError());
    thrd_exit(1);
  }

  if (SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0xE0, 0xFF) != 0) {
    outputLine("SetRenderDrawColor error: %s", SDL_GetError());
    thrd_exit(2);
  }

  if (SDL_RenderClear(renderer) != 0) {
    outputLine("RenderClear error: %s", SDL_GetError());
    thrd_exit(3);
  }

  menuItems.font = TTF_OpenFont("DejaVuSansMono.ttf", 16);
  if (menuItems.font == NULL) {
    outputLine("TTF_OpenFont() Error: %s", TTF_GetError());
    thrd_exit(3);
  }

  SDL_GetWindowSize(window, &window_width, &window_height);

  currItem = 0;
  mil_generateTextures(renderer, currList, currItem);

  done = 0;
  while (!done) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
        case SDL_WINDOWEVENT_EXPOSED:
          SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0xE0, 0xFF);
          SDL_RenderClear(renderer);
          break;
        }
        break;
      case SDL_QUIT:
        done = 1;
        break;
#ifndef NXDK
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          if (currItem == 0) {
            currItem = currList->length - 1;
          } else {
            --currItem;
          }
          mil_updatePrevCurrAndNextTexture(renderer, currList, currItem);
          break;
        case SDLK_DOWN:
          currItem = (currItem + 1) % currList->length;
          mil_updatePrevCurrAndNextTexture(renderer, currList, currItem);
          break;
        }
        break;
#endif
      default:
        break;
      }
    }
#ifdef NXDK
    XInput_GetEvents();
    for (i = 0; i < XInputGetPadCount(); ++i) {
      if (getDigitalKeyDown(&g_Pads[i], XPAD_DPAD_UP)) {
        if (currItem == 0) {
          currItem = menuItems.length - 1;
        } else {
          --currItem;
        }
        mil_updatePrevCurrAndNextTexture(renderer, currList, currItem);
      }
      if (getDigitalKeyDown(&g_Pads[i], XPAD_DPAD_DOWN)) {
        currItem = (currItem + 1) % currList->length;
        mil_updatePrevCurrAndNextTexture(renderer, currList, currItem);
      }
    }
#endif
    mil_drawMenuItems(renderer, currList);
    finishRendering(renderer);
  }
  mil_free(&menuItems);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  thrd_exit(0);
}

void finishRendering(SDL_Renderer *renderer) {
  SDL_RenderPresent(renderer);
#ifdef NXDK
  XVideoWaitForVBlank();
#endif
}
