#include "world.h"
#include "window.h"
extern Window window;
World::World(){
	srand(time(0));
	plant();
	noise();
	max45();
	clearExtraIslands();
}
void World::makeIsland(int x, int y){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if((i==0||i==3) && (j==0||j==3)) continue;
			land[x+i][y+j]=1;
		}
	}
}
void World::plant(){
	int margin=w;
	int fullSlice=(w*h/nIslands);
	int slice=fullSlice-margin*2;
	for(int i=0; i<nIslands; i++){
		int j=margin+rand()%slice+fullSlice*i;
		int x=j%w;
		int y=j/h;
		printf("%d,%d\n",x,y);
		makeIsland(x,y);
		islands[i][0]=x+1;
		islands[i][1]=y;
	}
}
void World::noise(){
	for(int x=0; x<w; x++){
		for(int y=0; y<h; y++){
			if(!land[x][y]) land[x][y]=rand()%100<landProb;
		}
	}
}
void World::max45(){
	bool changed;
	do{
		changed=false;
		for(int x=0; x<w; x++){
			for(int y=0; y<h; y++){
				int sum=0;
				for(int i=-1; i<=1; i++){
					for(int j=-1; j<=1; j++){
						if(!(y+j==0 || y+j==h)) sum+=land[(x+w+i)%w][y+j]%2;
					}
				}
				if((sum>4) != (land[x][y]%2)){
					land[x][y]+=2;
					changed=true;
				}
			}
		}
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
		if(land[x][y]>1) land[x][y]=3-land[x][y];
	}while(changed);
}
void World::clearExtraIslands(){
	for(int i=0; i<nIslands; i++){
		land[islands[i][0]][islands[i][1]]=2;
	}
	bool changed;
	do{
		changed=false;
		for(int x=0; x<w; x++)
			for(int y=0; y<h; y++)
				for(int i=-1; i<=1; i++)
					for(int j=-1; j<=1; j++)
						if(land[(x+w+i)%w][(y+h+j)%h]==2 && land[x][y]==1){
							land[x][y]=2;
							changed=true;
						}
	}while(changed);
	for(int x=0; x<w; x++){
		for(int y=0; y<h; y++){
			if(land[x][y]) land[x][y]--;
		}
	}
}
void World::draw(){
	//printf("displaying\n");
	SDL_Rect square={0,0,0,0};
	float scale=(float)window.screenWidth/w;
	for(int x=0; x<w; x++){
		for(int y=0; y<h; y++){
			if(land[x][y]) SDL_SetRenderDrawColor(window.ren,0,127,0,255);
			else SDL_SetRenderDrawColor(window.ren,0,0,127,255);
			square.x=x*scale;
			square.y=y*scale;
			square.w=(x+1)*scale-square.x+1;
			square.h=(y+1)*scale-square.y+1;
			square.x+=window.xOffset;
			square.y+=window.yOffset;
			SDL_RenderFillRect(window.ren,&square);
		}
	}
}
