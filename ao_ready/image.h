#pragma once
#include <vector>
#include <string>

struct Image
{
private:
	int m_width;
	int m_height;

	std::vector<uint8_t> m_pixels;
public:
	Image();

	bool load_from_file(const std::string& path);
	bool load_from_memory(const void* data, std::size_t size_in_bytes);

	bool save_to_file(const std::string& path);

	const void* get_pixels() const;
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
};

