#include"window.h"
#include"includes.h"
const double aspectRatio=1.777777778;
Window::Window(char *name){
    screenWidth=640;
    screenHeight=360;
	SDL_GetDesktopDisplayMode(0,&desktop);
	win=SDL_CreateWindow(name,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,360,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE),
    ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_SOFTWARE);
    fullscreen=false;
}
void Window::setAspect(){
    if(screenHeight*aspectRatio<screenWidth){
		yOffset=0;
		xOffset=(screenWidth-screenHeight*aspectRatio)/2;
		screenWidth=screenHeight*aspectRatio;
	}
	else{
		xOffset=0;
		yOffset=(screenHeight-screenWidth/aspectRatio)/2;
		screenHeight=screenWidth/aspectRatio;
	}
}
void Window::toggleFullscreen(){
    fullscreen=!fullscreen;
    screenWidth=fullscreen?desktop.w:640;
    screenHeight=fullscreen?desktop.h:360;
    SDL_SetWindowSize(win,screenWidth,screenHeight);
    setAspect();
    SDL_SetWindowFullscreen(win,fullscreen?SDL_TRUE:SDL_FALSE);
}
void Window::setSize(SDL_Event e){
    screenWidth=e.window.data1;
    screenHeight=e.window.data2;
    setAspect();
}
