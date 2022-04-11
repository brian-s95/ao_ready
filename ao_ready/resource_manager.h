#pragma once
#include <memory>
#include <string>
#include <vector>
#include <SDL_rect.h>
 
struct GrhData
{
	int file_num{};
	int frame_count{};
	SDL_Rect region{};
	std::vector<int> frames;
	float speed{};
};

struct GrhFxAnimationData
{
	int grh_id;
	int head_offset_x;
	int head_offset_y;
};

struct GrhAnimationData
{
	int up_animation_id;
	int down_animation_id;
	int left_animation_id;
	int right_animtion_id;

	int offset_x{};
	int offset_y{};
};

class ResourceManager final
{
private:
	std::vector<GrhData> m_grh_list;
	std::vector<GrhAnimationData> m_bodies;
	std::vector<GrhAnimationData> m_heads;
	std::vector<GrhAnimationData> m_helmets;
	std::vector<GrhAnimationData> m_weapons;
	std::vector<GrhAnimationData> m_shields;
	std::vector<GrhFxAnimationData> m_fxs;

	void load_heads(const std::string& path);
	void load_helmet(const std::string& path);
	void load_bodies(const std::string& path);
	void load_weapons(const std::string& path);
	void load_shields(const std::string& path);
	void load_fxs(const std::string& path);
	void load_grh_data(const std::string& path);
public:
	
	void load_resources();

	const GrhData* get_grh(int id) const { return &m_grh_list[id]; }

	const GrhAnimationData* get_body(int id) const { return &m_bodies[id]; }
	const GrhAnimationData* get_head(int id) const { return &m_heads[id]; }
	const GrhAnimationData* get_helmet(int id) const { return &m_helmets[id]; }
	const GrhAnimationData* get_weapon(int id) const { return &m_weapons[id]; }
	const GrhAnimationData* get_shield(int id) const { return &m_shields[id]; }
	const GrhFxAnimationData* get_fx(int id) const { return &m_fxs[id]; }
};

//extern std::unique_ptr<ResourceManager> g_resource_manager;
