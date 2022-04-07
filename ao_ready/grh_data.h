#pragma once
#include <vector>
#include <cstdint>

struct GrhData
{
	int file_num{};


	int frame_count{};
	std::vector<int> frames;
};