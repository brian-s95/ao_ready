#include <SDL.h>
#include <iostream>
#include <memory>

#include "renderer.h"

int main(int argc, char** args)
{	
	auto window = SDL_CreateWindow("Argentum Online 0.13.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	auto renderer = std::make_unique<Renderer>();
	auto run = true;

	renderer->init(window, false);

	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}

		renderer->render_clear({32u, 32u, 34u, 255u});
		renderer->render_present();
	}

	renderer->cleanup();
	SDL_DestroyWindow(window);
	return 0;
} 