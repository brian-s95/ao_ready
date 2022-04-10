#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace FileSystem
{
	std::vector<uint8_t> read_all_bytes(const std::string& path);
}

