#include "resource_manager.h"
#include "filesystem_utils.h"
#include "byte_buffer.h"

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
}
