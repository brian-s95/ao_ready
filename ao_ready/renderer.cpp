#include <SDL.h>
#include <SDL_image.h>
#include <sstream>
#include <cmath>

#include "renderer.h"
#include "texture.h"
#include "image.h"

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

Texture* Renderer::get_texture(const std::string& path)
{
	auto found = m_textures.find(path);
	if (found != m_textures.end()) {
		return found->second.get();
	}
	
	auto surface = IMG_Load(path.c_str());
	if (!surface)
	{
		std::ostringstream error_msg;
		error_msg << "failed to load image " << path
				  << " \nSDL Error " << IMG_GetError();

		throw std::runtime_error(error_msg.str());
	}

	auto resource = SDL_CreateTextureFromSurface(m_renderer, surface);
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

	m_textures.emplace(path, texturePtr);
	return m_textures[path].get();
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

	SDL_FRect abs_rect;
	abs_rect.x = dst.x - camera_position.x;
	abs_rect.y = dst.y - camera_position.y;
	abs_rect.w = dst.w;
	abs_rect.h = dst.h;

	SDL_RenderCopyF(m_renderer, texture->get_resource(), &src, &abs_rect); 
}

void Renderer::draw_rect(SDL_Rect rect, SDL_Color color, bool fill)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_FPoint position = m_camera.get_position();

	rect.x -= static_cast<int>(std::roundf( position.x));
	rect.y -= static_cast<int>(std::roundf(position.y));

	if (fill)
		SDL_RenderFillRect(m_renderer, &rect);
	else
		SDL_RenderDrawRect(m_renderer, &rect);

}

void Renderer::draw_line(SDL_Point start, SDL_Point end, SDL_Color color)
{
	SDL_FPoint position = m_camera.get_position();

	start.x -= static_cast<int>(position.x);
	start.y -= static_cast<int>(position.y);
	end.x	-= static_cast<int>(position.x);
	end.y	-= static_cast<int>(position.y);

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_renderer, start.x, start.y, end.x, end.y);
}

void Renderer::draw_lines(const SDL_Point* points, std::size_t count, SDL_Color color)
{
	SDL_FPoint position = m_camera.get_position();
	SDL_Point start;
	SDL_Point end;

	if (count % 2 == 0)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		
		for (size_t i = 0; i < count; i += 2)
		{
			start = points[i];
			end = points[i + 1];

			start.x -= static_cast<int>(position.x);
			start.y -= static_cast<int>(position.y);
			end.x	-= static_cast<int>(position.x);
			end.y	-= static_cast<int>(position.y);

			SDL_RenderDrawLine(m_renderer, start.x, start.y, end.x, end.y);
		}
	}
}

void Renderer::render_clear()
{
	render_clear({ 0u,0u,0u,255u });
}

void Renderer::render_clear(SDL_Color color)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer); 
}

void Renderer::render_present()
{
	SDL_RenderPresent(m_renderer);
}
