#include <SDL2/SDL.h>

#include <iostream>
#include "ball.hpp"

int x_vault;

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect srcBg = { 0,128, 96,128 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect scrVaiss = { 128,0,128,32 };

Ball b;

void init()
{
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./sprites.bmp");
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

	//initialize the ball
	b.init(win_surf->w /2, win_surf->h /2, 5, 7);
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
	// remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
	for (int j = 0; j < win_surf->h; j+=128)
		for (int i = 0; i < win_surf->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
		}

	
	// draw the ball
	b.draw(plancheSprites, win_surf);

	// update the ball
	b.update(win_surf, x_vault);
	
	// vaisseau
	dest.x = x_vault;
	dest.y = win_surf->h - 32;
	SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);
}



int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
		return 1;
    }

	init();
    
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					// touche clavier
					case SDLK_LEFT:  x_vault -= 10; break;
					case SDLK_RIGHT: x_vault +=10; break;
					case SDLK_ESCAPE: quit = true; break;
					default: break;
				}
				break;
			case SDL_MOUSEMOTION:	x_vault += event.motion.xrel;	break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "mouse click " << event.button.button << std::endl;
				break;
			default: break;
			}
		}
		draw();
		SDL_UpdateWindowSurface(pWindow); 
		SDL_Delay(20); // 50 fps
	}
    SDL_Quit();
    return 0;
}
