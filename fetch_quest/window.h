#ifndef WINDOW_H
#define WINDOW_H
#include"includes.h"
struct Window{
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_DisplayMode desktop;
    bool fullscreen;
    Uint16 screenWidth,screenHeight,xOffset,yOffset;
    Window(char*);
    void setAspect();
    void toggleFullscreen();
    void setSize(SDL_Event e);
};
#endif // WINDOW_H_INCLUDED
