#pragma once
#include <unordered_map>
#include <string>
#include <SDL_rect.h>

#include "definitions.h"
#include "camera.h"

struct SDL_Renderer;
struct SDL_Window;
class Texture;



class Renderer final
{
private:
	SDL_Renderer*	m_renderer;
	SDL_Window*		m_window; 
	Camera			m_camera;
	
	std::unordered_map<std::string, Ref<Texture>> m_textures;
public:
	Renderer();
	~Renderer();

	Renderer(const Renderer&) = delete;
	const Renderer& operator=(const Renderer&) = delete;

	void init(SDL_Window* window, bool vsync);
	void cleanup();

	Texture* get_texture(const std::string& path);
	SDL_Renderer* get_sdl_renderer() const { return m_renderer; }

	void set_camera(const Camera& camera) { m_camera = camera; }
	Camera get_camera() const { return m_camera; }

	void draw_texture(Texture* texture, float x, float y, const SDL_Rect& src);
	void draw_texture(Texture* texture, float x, float y, const SDL_Rect& src, SDL_Color color);

	void draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src);
	void draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src, SDL_Color color);

	void draw_rect(SDL_Rect rect, SDL_Color color, bool fill = false);

	void draw_line(SDL_Point start, SDL_Point end, SDL_Color color);
	void draw_lines(const SDL_Point* points, std::size_t count, SDL_Color color);

	void render_clear();
	void render_clear(SDL_Color color);
	void render_present(); 
};

extern std::unique_ptr<Renderer> g_renderer;
