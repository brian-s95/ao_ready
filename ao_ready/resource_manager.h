#pragma once
#include <memory>
#include <string>
#include <vector>

#include "grh_data.h"

class ResourceManager final
{
private:
	std::vector<GrhData> m_grh_list;

	void load_grh_data(const std::string& path);
public:
	
	void load_resources();

	const GrhData* get_grh(int id) const { return &m_grh_list[id]; }
};

extern std::unique_ptr<ResourceManager> g_resource_manager;