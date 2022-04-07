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






	return false;
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
