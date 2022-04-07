#include <SDL.h>
#include <sstream>

#include "renderer.h"
#include "texture.h"
#include "image.h"
#include <iostream>

Renderer::Renderer()
:m_renderer(nullptr)
,m_window(nullptr)
{
}

Renderer::~Renderer()
{
	cleanup();
}

void Renderer::init(SDL_Window* window, bool vsync)
{
	uint32_t settings = SDL_RENDERER_ACCELERATED;
	if (vsync) settings |= SDL_RENDERER_PRESENTVSYNC;

	m_window = window;
	m_renderer = SDL_CreateRenderer(m_window, -1, settings);

	if (!m_renderer)
	{
		std::ostringstream error_str;
		error_str << "failed to create renderer\n SDL_ERROR: " << SDL_GetError();
		throw std::runtime_error(error_str.str());
	}
}

void Renderer::cleanup()
{
	m_textures.clear();
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

Texture* Renderer::get_texture(int id)
{
	auto found = m_textures.find(id);
	if (found != m_textures.end()) {
		return found->second.get();
	}

	std::string path = "resources/graphics/" + std::to_string(id) + ".bmp";
	Image image;

	if (!image.load_from_file(path))
	{
		std::ostringstream error_str;
		error_str << "failed to create image\n PATH_ERROR: " << path;
		throw std::runtime_error(error_str.str());
	}

	auto surface = new SDL_Surface;

	SDL_Texture* resource = SDL_CreateTextureFromSurface(m_renderer, surface);

	if (!resource) 
	{
		std::ostringstream error_msg;
		error_msg << "Unable to create texture from " << path
			<< " \nSDL Error " << SDL_GetError();

		SDL_FreeSurface(surface);
		throw std::runtime_error(error_msg.str());
	}

	auto texturePtr = std::make_shared<Texture>(resource, surface->w, surface->h);
	SDL_FreeSurface(surface);

	m_textures.emplace(id, texturePtr);
	return m_textures[id].get();
}

void Renderer::draw_texture(Texture* texture, float x, float y, const SDL_Rect& src)
{
	draw_texture(texture, x, y, src, { 255u,255u,255u,255u });
}

void Renderer::draw_texture(Texture* texture, float x, float y, const SDL_Rect& src, SDL_Color color)
{
	SDL_FRect dst;
	dst.x = x;
	dst.y = y;
	dst.w = static_cast<float>(src.w);
	dst.h = static_cast<float>(src.h);

	draw_texture(texture, dst, src, color);
}

void Renderer::draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src)
{
	draw_texture(texture, dst, src, { 255u,255u,255u,255u });
}

void Renderer::draw_texture(Texture* texture, const SDL_FRect& dst, const SDL_Rect& src, SDL_Color color)
{
	SDL_SetTextureColorMod(texture->get_resource(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture->get_resource(), color.a);

	SDL_FPoint camera_position = m_camera.get_position();
	if (!m_camera.object_is_visible(dst))
	{ 
		omitido += 1;
		return;
 	}

	SDL_FRect abs_rect;
	abs_rect.x = dst.x - camera_position.x;
	abs_rect.y = dst.y - camera_position.y;
	abs_rect.w = dst.w;
	abs_rect.h = dst.h;

	SDL_RenderCopyF(m_renderer, texture->get_resource(), &src, &abs_rect);

	dibujado += 1;
}

void Renderer::render_clear()
{
	render_clear({ 0u,0u,0u,255u });
}

void Renderer::render_clear(SDL_Color color)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	dibujado = 0;
	omitido = 0;
}

void Renderer::render_present()
{
	SDL_RenderPresent(m_renderer);
}
