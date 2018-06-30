#include <iostream>
#include <SDL.h>


void	poll_event(){

	SDL_Event	e;
	
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			exit(-1);
	}
}

int main ()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		exit (0);
	}
	// Cpu cpu;
	// Ram ram;

	// ram.readTop();
	// ram.parseUsage();
	// ram.init();
	// cpu.run();
	SDL_Window	*win;
	SDL_Renderer *render;
	SDL_Surface *surf;
	unsigned int *buff;

	win = SDL_CreateWindow("Strapony", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		exit (0);
	}
	surf = SDL_GetWindowSurface(win);
	// render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	// if (render == NULL)
	// {
	// 	std::cout << SDL_GetError() << std::endl;
	// 	exit (0);
	// }
	buff = (unsigned int *)surf->pixels;
	SDL_Rect rect;
	rect.x = rect.y = 10;
	rect.w = 150;
	rect.h = 150;

int z = 0;
		bzero(surf->pixels, 640 * 480 * 4);
	while (true)
	{
		poll_event();

		for (int k = 20; k < 50; k++) {
			// z++;
		bzero(surf->pixels, 640 * 480 * 4);
			for (int i = k; i < 50+k; ++i)
			{
				for (int j = 0; j < 50; ++j)
				{
					buff[640 * j + i] = 0xff;
				}
			}
		}
		// SDL_UpdateWindowSurface(win);
		// SDL_RenderClear(render);
		// SDL_SetRenderDrawColor(render, 200, 0, 0, 0);
		// SDL_RenderFillRect(render, &rect);
		// SDL_SetRenderDrawColor(render, 0, 0, 0, 0);


		// SDL_RenderPresent(render);
		// SDL_FillRect(surf, &rect, 0xff);
		SDL_UpdateWindowSurface(win);
	}
	SDL_Delay(5000);
	SDL_Quit();
	return (0);
}