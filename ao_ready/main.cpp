#include <SDL.h>
#include <iostream>
#include <memory>

#include "texture.h"
#include "renderer.h"

int main(int argc, char** args)
{	
	auto window = SDL_CreateWindow("Argentum Online 0.13.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	auto renderer = std::make_unique<Renderer>();
	renderer->init(window, false);
	auto run = true;

	auto surface = SDL_LoadBMP(R"(C:\Users\monchi\source\repos\Arlen\Arlen\aoaugraficos.bmp)");
	auto texture_ptr = SDL_CreateTextureFromSurface(renderer->get_sdl_renderer(), surface);
	std::cout << SDL_GetError() << std::endl;

	auto texture = std::make_unique<Texture>(texture_ptr, surface->w, surface->h);
	auto camera = Camera(1280, 720);
	 
	auto speed = 200.0f;

	auto key_maps = std::unordered_map<int, SDL_FPoint>
	{
		{SDL_SCANCODE_UP, {0.f, -1.0f}},
		{SDL_SCANCODE_DOWN, {0.f, 1.0f}},
		{SDL_SCANCODE_LEFT, {-1.0f, 0.0f}},
		{SDL_SCANCODE_RIGHT, {1.0f, 0.0f}}
	};

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float delta_time = 0;

	srand(time(nullptr));

	std::vector<SDL_FPoint> sprites;
	for (size_t x = 0; x < 30000; x++)
	{
		float pos_x = rand() % 32000;
		float pos_y = rand() % 32000;

		sprites.push_back({ pos_x, pos_y });
	}
	


	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}

		auto keyboard_state_array = SDL_GetKeyboardState(nullptr);
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		delta_time = (float)((NOW - LAST) * 1000 / (float)SDL_GetPerformanceFrequency());
		

		SDL_FPoint velocity{};
		for (const auto& key : key_maps)
		{
			if (keyboard_state_array[key.first]) 
			{
				velocity.x += key.second.x;
				velocity.y += key.second.y;
			}
		}

		float offset_x = (velocity.x * speed) * (delta_time / 1000.f);
		float offset_y = (velocity.y * speed) * (delta_time / 1000.f);

		camera.move(offset_x, offset_y);

		renderer->set_camera(camera);
		renderer->render_clear(/*{32u, 32u, 34u, 255u}*/);


		for (const auto& sprite : sprites)
		{
			renderer->draw_texture(texture.get(), sprite.x, sprite.y, texture->get_texture_rect());
		}

		renderer->render_present();
		std::cout << "dibujado " << renderer->dibujado << " omitido " << renderer->omitido << std::endl;
	}

	renderer->cleanup();
	SDL_DestroyWindow(window);
	return 0;
} 