#include <SDL.h>
#include "texture.h"

Texture::Texture(SDL_Texture* resource, int width, int height)
:m_resource(resource)
,m_width(width)
,m_height(height)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_resource);
}

SDL_Rect Texture::get_texture_rect() const
{
	return { 0, 0, m_width, m_height };
}
