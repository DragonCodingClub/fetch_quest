#ifndef WORLD_H
#define WORLD_H
#include "includes.h"
//width, height
static const int w=128, h=72, landProb=45, nIslands=7;
struct World{
	Uint8 land[w][h];
	Uint8 islands[nIslands][2];
	//constructor
	World();
	//places the smallest possible island from x,y to x+3,y+3
	void makeIsland(int x, int y);
	//places islands at decided locations
	void plant();
	//fills the land map with random noise according to landProb
	void noise();
	//applies 4/5 rule to map until no change
	void max45();
	//clears extra islands
	void clearExtraIslands();
	//draws map to renderer
	void draw();
};
#endif // WORLD_H
