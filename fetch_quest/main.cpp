#include "includes.h"
#include "world.h"
#include "window.h"
World world;
Window window=Window((char*)"Commerce: The Game!");
int main(int argc, char* args[]){
	SDL_Event e;
	bool running=true;
	for(Uint32 frame=0;running;frame++){
		//handle events
		while(SDL_PollEvent(&e)){
			if(e.type==SDL_QUIT){
				running=false;
				break;
			}
            else if(e.type==SDL_KEYDOWN){
                if(e.key.keysym.sym==SDLK_F11) window.toggleFullscreen();
            }
			else if(e.type==SDL_WINDOWEVENT && e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED){
                window.setSize(e);
			}
		}
		//clear renderer
		SDL_SetRenderDrawColor(window.ren,0,0,0,255);
		SDL_RenderClear(window.ren);
		//redraw world
		world.draw();
		//present renderer
		SDL_RenderPresent(window.ren);
		//regulate frame rate
		Uint32 nextFrameTicks=(frame)*1000.0/60;
        if(nextFrameTicks>SDL_GetTicks()) SDL_Delay(nextFrameTicks-SDL_GetTicks());
	}
	return 0;
}
