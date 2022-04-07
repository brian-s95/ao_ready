#pragma once
#include <unordered_map>
#include <SDL_rect.h>

#include "defines.h"

struct SDL_Renderer;
struct SDL_Window;
class Texture;

class Renderer final
{
private:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window; 
	
	std::unordered_map<int, Ref<Texture>> m_textures;
public:
	Renderer();
	~Renderer();

	Renderer(const Renderer&) = delete;
	const Renderer& operator=(const Renderer&) = delete;

	void init(SDL_Window* window, bool vsync);
	void cleanup();

	Texture* get_texture(int id);

	void draw_texture(Texture* texture, float x, float y, const SDL_Rect& src);
	void draw_texture(Texture* texture, float x, float y, const SDL_Rect& src, SDL_Color color);

	void draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src);
	void draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src, SDL_Color color);

	void render_clear();
	void render_clear(SDL_Color color);
	void render_present();
};

