#pragma once
#include <vector>
#include <cstdint>
#include <SDL_rect.h>

struct GrhData
{
	int file_num{};
	int frame_count{};
	SDL_Rect region{};
	std::vector<int> frames;
	float speed{};
};