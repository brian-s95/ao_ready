#include "resource_manager.h"
#include "filesystem_utils.h"
#include "byte_buffer.h"
#include "init_file.h"

void ResourceManager::load_grh_data(const std::string& path)
{
	auto bytes = FileSystem::read_all_bytes(path);
	ByteBuffer reader(bytes.data(), bytes.size());

	//file version
	reader.read_i32();

	//grh count
	int grh_count = reader.read_i32();

	m_grh_list.resize(grh_count + 1);

	while (reader.position() < reader.size())
	{
		int grh_id = reader.read_i32();
		GrhData& grh = m_grh_list[grh_id];

		grh.frame_count = reader.read_i16();
		grh.frames.resize(grh.frame_count + 1);

		if (grh.frame_count > 1)
		{
			for (int i = 1; i <= grh.frame_count ; i++)
			{
				grh.frames[i] = reader.read_i32();
			}
			grh.speed = reader.read_float();

			grh.region.w = m_grh_list[grh.frames[1]].region.w;
			grh.region.h = m_grh_list[grh.frames[1]].region.h;
		}
		else
		{
			grh.file_num = reader.read_i32();
			grh.frames[1] = grh_id;

			grh.region.x = reader.read_i16();
			grh.region.y = reader.read_i16();
			
			grh.region.w = reader.read_i16();
			grh.region.h = reader.read_i16();
		}
 	}

}

void ResourceManager::load_resources()
{
	load_grh_data("data/init/graphics.ind");

	load_bodies("data/init/personajes.ind");
	load_heads("data/init/cabezas.ind");
	load_helmet("data/init/cascos.ind");
	load_weapons("data/init/armas.dat");
	load_shields("data/init/escudos.dat");
	load_fxs("data/init/fxs.ind");
}

void ResourceManager::load_heads(const std::string &path)
{
	auto bytes = FileSystem::read_all_bytes(path);
	ByteBuffer reader(bytes.data(), bytes.size());

	//header
	reader.skip(255 + 4 + 4);

	int count = reader.read_i16();
	m_heads.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		auto& head = m_heads[i];
		head.up_animation_id = reader.read_i16();
		head.right_animtion_id = reader.read_i16();
		head.down_animation_id = reader.read_i16();
		head.left_animation_id = reader.read_i16();
	}
}

void ResourceManager::load_helmet(const std::string &path)
{
	auto bytes = FileSystem::read_all_bytes(path);
	ByteBuffer reader(bytes.data(), bytes.size());

	//header
	reader.skip(255 + 4 + 4);

	int count = reader.read_i16();
	m_helmets.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		auto& helmet = m_helmets[i];
		helmet.up_animation_id = reader.read_i16();
		helmet.right_animtion_id = reader.read_i16();
		helmet.down_animation_id = reader.read_i16();
		helmet.left_animation_id = reader.read_i16();
	}
}

void ResourceManager::load_bodies(const std::string &path)
{
	auto bytes = FileSystem::read_all_bytes(path);
	ByteBuffer reader(bytes.data(), bytes.size());

	//header
	reader.skip(255 + 4 + 4);

	int count = reader.read_i16();
	m_bodies.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		auto& body = m_bodies[i];
		body.up_animation_id = reader.read_i16();
		body.right_animtion_id = reader.read_i16();
		body.down_animation_id = reader.read_i16();
		body.left_animation_id = reader.read_i16();

		body.offset_x = reader.read_i16();
		body.offset_y = reader.read_i16();
	}
}

void ResourceManager::load_weapons(const std::string &path)
{
	InitFile init;
	init.read_from_file(path);

	int count = std::stoi(init.read_data("init", "NumArmas"));
	m_weapons.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		if(i == 2) continue; //No animar

		auto& weapon = m_weapons[i];
		weapon.up_animation_id   = std::stoi(init.read_data("ARMA" + std::to_string(i), "Dir1"));
		weapon.right_animtion_id = std::stoi(init.read_data("ARMA" + std::to_string(i), "Dir2"));
		weapon.down_animation_id = std::stoi(init.read_data("ARMA" + std::to_string(i), "Dir3"));
		weapon.left_animation_id = std::stoi(init.read_data("ARMA" + std::to_string(i), "Dir4"));
	}
}

void ResourceManager::load_shields(const std::string &path)
{
	InitFile init;
	init.read_from_file(path);

	int count = std::stoi(init.read_data("INIT", "NumEscudos"));
	m_shields.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		if(i == 2) continue; //No animar

		auto& shield = m_shields[i];
		shield.up_animation_id   = std::stoi(init.read_data("ESC" + std::to_string(i), "Dir1"));
		shield.right_animtion_id = std::stoi(init.read_data("ESC" + std::to_string(i), "Dir2"));
		shield.down_animation_id = std::stoi(init.read_data("ESC" + std::to_string(i), "Dir3"));
		shield.left_animation_id = std::stoi(init.read_data("ESC" + std::to_string(i), "Dir4"));
	}
}

void ResourceManager::load_fxs(const std::string &path)
{
	auto bytes = FileSystem::read_all_bytes(path);
	ByteBuffer reader(bytes.data(), bytes.size());

	//header
	reader.skip(255 + 4 + 4);

	int count = reader.read_i16();
	m_fxs.resize(count + 1);

	for(int i = 1; i <= count; ++i)
	{
		auto& fx = m_fxs[i];
		fx.grh_id = reader.read_i16();
		fx.head_offset_x = reader.read_i16();
		fx.head_offset_y = reader.read_i16();
	}
}
