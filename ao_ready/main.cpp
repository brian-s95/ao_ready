#include <SDL.h>
#include <iostream>
#include <memory>

#include "texture.h"
#include "renderer.h"
#include "camera.h"
#include "resource_manager.h"
#include "map.h"

std::unique_ptr<Renderer> g_renderer;
std::unique_ptr<ResourceManager> g_resource_manager;

struct Animation
{
	std::vector<SDL_Rect> frames;
	Texture* sprite_sheet;

	void add_frame(const SDL_Rect& frame)
	{
		frames.push_back(frame);
	}

	std::size_t size() const { return frames.size(); }
	SDL_Rect get_frame(std::size_t id) { return frames[id]; }
};

int main(int argc, char** args)
{	
	srand(time(nullptr));
	
	auto window = SDL_CreateWindow("Argentum Online 0.13.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	g_renderer = std::make_unique<Renderer>();
	g_renderer->init(window, false);

	g_resource_manager = std::make_unique<ResourceManager>();
	g_resource_manager->load_resources();

	Map map;
	map.load_from_file("data/mapas/mapa1.map");

	auto camera = Camera(1280, 720);
	auto speed = 200.0f;

	auto texture = g_renderer->get_texture("data/graphics/3099.png");
	SDL_SetTextureBlendMode(texture->get_resource(), SDL_BLENDMODE_ADD);

	Animation animation;
	animation.sprite_sheet = texture;
	
	int w = texture->get_width() / 5;
	int h = texture->get_height() / 2;

	for (size_t x = 0; x < 5; x++)
	{
		SDL_Rect frame;
		frame.x = x * w;
		frame.y = 0;
		frame.w = w;
		frame.h = h;

		animation.add_frame(frame);
	}

	for (size_t x = 0; x < 5; x++)
	{
		SDL_Rect frame;
		frame.x = x * w;
		frame.y = h;
		frame.w = w;
		frame.h = h;

		animation.add_frame(frame);
	}

	int current_frame = 0;
	float time = 0.0f;
	const float max_time = 0.04f;

	auto key_maps = std::unordered_map<int, SDL_FPoint>
	{
		{SDL_SCANCODE_UP, {0.f, -1.0f}},
		{SDL_SCANCODE_DOWN, {0.f, 1.0f}},
		{SDL_SCANCODE_LEFT, {-1.0f, 0.0f}},
		{SDL_SCANCODE_RIGHT, {1.0f, 0.0f}}
	};

	auto get_tick = [](uint64_t& clock) -> float
	{
		uint64_t last = clock;
		uint64_t now = SDL_GetTicks64();
		clock = now;

		uint64_t elapsed = now - last;
		return static_cast<float>(elapsed) / 1000.f;
	};
	uint64_t clock = SDL_GetTicks64();

	 
	auto run = true;
	while (run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
		}

		int x; int y;
		SDL_GetMouseState(&x, &y);
		x += camera.get_position().x;
		y += camera.get_position().y;

		auto keyboard_state_array = SDL_GetKeyboardState(nullptr);

		float dt = get_tick(clock);

		time += dt;
		if (time > max_time)
		{
			current_frame = (current_frame + 1) % animation.size();
			time = 0;
		}
		 
		SDL_FPoint velocity{};
		for (const auto& key : key_maps)
		{
			if (keyboard_state_array[key.first]) 
			{
				velocity.x += key.second.x;
				velocity.y += key.second.y;
			}
		}

		float offset_x = (velocity.x * speed) * dt;
		float offset_y = (velocity.y * speed) * dt;

		camera.move(offset_x, offset_y);

		g_renderer->set_camera(camera);
		g_renderer->render_clear({32u, 32u, 34u, 255u});
		g_renderer->draw_rect({ 0, 0, 3200, 3200 }, {255, 0, 0, 255}, true);
		g_renderer->draw_texture(texture, 600, 50, animation.get_frame(current_frame), {255, 255, 255, 255});

		map.draw(camera);
		g_renderer->draw_texture(texture, x - (w / 2), y - (h / 2), animation.get_frame(current_frame), { 255, 255, 255, 155 });
		g_renderer->render_present();
	}

	g_renderer->cleanup();
	SDL_DestroyWindow(window);
	return 0;
} 