#pragma once
#include <SDL_rect.h>

struct SDL_Texture;

class Texture
{
private:
	SDL_Texture*	m_resource;
	int				m_width;
	int				m_height;

public:
	Texture(SDL_Texture* resource, int width, int height);
	~Texture();

	Texture(const Texture&) = delete;
	const Texture& operator=(const Texture&) = delete;
	
	SDL_Texture* get_resource() const { return m_resource; }
	SDL_Rect get_texture_rect() const;

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
};

