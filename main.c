#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Surface *screen;

/* Main Loop */
void loop() {
  /* Loop through waiting messages and process them */
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    /* Closing the Window or pressing Escape will exit the program */
    if (event.type == SDL_QUIT) {
      exit(0);
    }
  }

  /* Lock the screen for direct access to the pixels */
  if (SDL_MUSTLOCK(screen)) {
    if (SDL_LockSurface(screen) < 0) {
      fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
    }
  }

  /* Set color */
  Uint32 color = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00);
  int bpp = screen->format->BytesPerPixel;
  Uint8 *pixel;

  /* Draw pixels to screen */
  for(int x=0;x<640;x++) {
    for(int y=0;y<480;y++) {
      bpp = 1;
      pixel = (Uint8 *)screen->pixels + y*screen->pitch + x * bpp;
      *pixel = color;
    }
  }

  /* Unlock screen */
  if (SDL_MUSTLOCK(screen)) {
    SDL_UnlockSurface(screen);
  }

  SDL_Flip(screen);
}

int main(int argc, char *argv[]) {
  /* Initialise SDL Video */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  /* Open a 640 x 480 screen */
  screen = SDL_SetVideoMode(640, 480, 8, SDL_HWSURFACE|SDL_DOUBLEBUF);

  if (screen == NULL) {
    printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());
    exit(1);
  }

  /* Set the screen title */
  SDL_WM_SetCaption("Red Screen", NULL);
  printf("BytesPerPixel: %d\n",  screen->format->BytesPerPixel);

#ifdef __EMSCRIPTEN__
  // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
  emscripten_set_main_loop(loop, 60, 1);
#else
  while (1) {
    loop();
    SDL_Delay(16);
  }
#endif

  return 0;
}
