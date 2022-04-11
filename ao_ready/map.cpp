#include "map.h"
#include "filesystem_utils.h"
#include "byte_buffer.h"
#include "camera.h"
#include "resource_manager.h"
#include "renderer.h"

void Map::draw_ground(const Camera& camera)
{
	int camera_start_x = camera.get_position().x;
	int camera_start_y = camera.get_position().y;

	int camera_width = camera.get_viewport_width();
	int camera_height = camera.get_viewport_height();

	int start_x = camera_start_x / TILE_SIZE;
	int start_y = camera_start_y / TILE_SIZE;

	int end_x = (camera_start_x + camera_width) / 32;
	int end_y = (camera_start_y + camera_height) / 32;

	for (int y = start_y; y < end_y + 1; y++)
	{
		for (int x = start_x; x < end_x + 1; x++)
		{
			if (in_map_bounds(x, y))
			{
				draw_tile(m_tiles[x + y * MAP_SIZE].ground, x * 32, y * 32);
				draw_tile(m_tiles[x + y * MAP_SIZE].coast_and_wall, x * 32, y * 32);
			}
		}
	}
}

void Map::draw_overlap(const Camera& camera)
{
	int camera_start_x = camera.get_position().x;
	int camera_start_y = camera.get_position().y;

	int camera_width = camera.get_viewport_width();
	int camera_height = camera.get_viewport_height();

	int start_x = camera_start_x / TILE_SIZE;
	int start_y = camera_start_y / TILE_SIZE;

	int end_x = (camera_start_x + camera_width) / 32;
	int end_y = (camera_start_y + camera_height) / 32;

	const int offfset = 8;

	for (int y = start_y - offfset; y < end_y + offfset; y++)
	{
		for (int x = start_x - offfset; x < end_x + offfset; x++)
		{
			if (in_map_bounds(x, y))
			{
				draw_tile(m_tiles[x + y * MAP_SIZE].overlap, x * 32, y * 32);
			}
		}
	}
}

void Map::draw_front(const Camera& camera)
{
	int camera_start_x = camera.get_position().x;
	int camera_start_y = camera.get_position().y;

	int camera_width = camera.get_viewport_width();
	int camera_height = camera.get_viewport_height();

	int start_x = camera_start_x / TILE_SIZE;
	int start_y = camera_start_y / TILE_SIZE;

	int end_x = (camera_start_x + camera_width) / 32;
	int end_y = (camera_start_y + camera_height) / 32;

	const int offfset = 8;

	for (int y = start_y - offfset; y < end_y + offfset; y++)
	{
		for (int x = start_x - offfset; x < end_x + offfset; x++)
		{
			if (in_map_bounds(x, y))
			{
				draw_tile(m_tiles[x + y * MAP_SIZE].front, x * 32, y * 32);
			}
		}
	}
}

void Map::draw_tile(int id, int x, int y)
{
	if (id == 0) return;

	//auto grh = g_resource_manager->get_grh(id);
	//if (grh->frame_count > 1)
	//	grh = g_resource_manager->get_grh(grh->frames[1]);

	//int tile_width = grh->region.w / TILE_SIZE;
	//int tile_height = grh->region.h / TILE_SIZE;
	//
	//if (tile_width != 1)
	//	x = x - (tile_width * TILE_SIZE / 2) + TILE_SIZE / 2;
	//
	//if (tile_height != 1)
	//	y = y - (tile_height * TILE_SIZE) + TILE_SIZE;
	//
	//Texture* texture = get_texture(grh->file_num);
	//g_renderer->draw_texture(texture, (float)x, (float)y, grh->region);
}

Texture* Map::get_texture(int id)
{
	//auto found = m_textures.find(id);
	//if (found != m_textures.end())
	//{
	//	return found->second;
	//}
	//else
	//{
	//	auto texture_ptr = g_renderer->get_texture("data/graphics/" + std::to_string(id) + ".png");
	//	m_textures.emplace(id, texture_ptr);
	//	return texture_ptr;
	//}
	return NULL;
}

Map::Map()
{
	m_tiles.resize(MAP_SIZE * MAP_SIZE);
}

Map::~Map()
{
}

void Map::load_from_file(const std::string& path)
{
	ByteBuffer reader;
	auto bytes = FileSystem::read_all_bytes(path);

	reader.write_data(bytes.data(), bytes.size());

	//map version
	reader.read_i16();

	//map header
	reader.skip(255 + 4 + 4);

	//tmp
	reader.skip(8);

	for (size_t y = 0; y < MAP_SIZE; y++)
	{
		for (size_t x = 0; x < MAP_SIZE; x++)
		{
			uint32_t flags = reader.read_u8();
			uint32_t tile_id = x + y * MAP_SIZE;

			auto& tile = m_tiles[tile_id];

			tile.ground = reader.read_i16();
			
			if (flags & 2)
				tile.coast_and_wall = reader.read_i16();

			if (flags & 4)
				tile.overlap = reader.read_i16();

			if (flags & 8)
				tile.front = reader.read_i16();

			if (flags & 16)
				tile.flags = reader.read_i16();
		}
	}
}

void Map::draw(const Camera& camera)
{
	draw_ground(camera);
	draw_overlap(camera);
	draw_front(camera);
}

 