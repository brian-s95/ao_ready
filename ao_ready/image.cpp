#define STB_IMAGE_IMPLEMENTATION
#include <SDL_rwops.h>

#include "image.h"
#include "stb_image.h"

Image::Image()
:m_width(0)
,m_height(0)
{
}

bool Image::load_from_file(const std::string& path)
{
	auto file_handle = SDL_RWFromFile(path.c_str(), "r+b");
	if (file_handle) 
	{
		return false;
	}

	Sint64 size = SDL_RWsize(file_handle);
	if(!file_handle)
	{
		SDL_RWclose(file_handle);
	}

	std::vector<uint8_t> data(size);
	SDL_RWread(file_handle, data.data(), size, 1);


	SDL_RWclose(file_handle);
	return true;
}

bool Image::load_from_memory(const void* data, std::size_t size_in_bytes)
{
	return false;
}

bool Image::save_to_file(const std::string& path)
{
	return false;
}

const void* Image::get_pixels() const
{
	return m_pixels.empty() ? nullptr : m_pixels.data();
}
