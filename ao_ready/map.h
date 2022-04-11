#pragma once
#include <array>
#include <vector>
#include <string>
#include <unordered_map>

#include "definitions.h"

class Camera;
class Texture;

class Map
{
public:
	struct TileData
	{
		int ground{};
		int coast_and_wall{};
		int overlap{};
		int front{};

		uint32_t flags{};
	};

private:
	std::vector<TileData> m_tiles;
	std::unordered_map<int, Texture*> m_textures;

	void draw_ground(const Camera& camera); 
	void draw_overlap(const Camera& camera);
	void draw_front(const Camera& camera);

	void draw_tile(int id, int x, int y);
	Texture* get_texture(int id);

public:
	Map();
	~Map();

	void load_from_file(const std::string& path);
	void draw(const Camera& camera);
	

	bool in_map_bounds(int x, int y)
	{
		return (x >= 0 && x < MAP_SIZE) &&
			(y >= 0 && y < MAP_SIZE);
	}
};

