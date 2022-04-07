#pragma once
#include <SDL_rect.h>

class Camera
{
private:
	int m_viewport_width;
	int m_viewport_height;

	SDL_Rect m_limits;
	SDL_FPoint m_position;
public:
	Camera();
	Camera(int viewport_width, int viewport_height);

	SDL_Rect get_viewport_rect() const;

	bool object_is_visible(const SDL_Rect& bounds);
	bool object_is_visible(const SDL_FRect& bounds);

	SDL_Rect transform(const SDL_Rect& rect) const;
	SDL_FRect transform(const SDL_FRect& rect) const;

	SDL_Point transform(const SDL_Point& point) const;
	SDL_FPoint transform(const SDL_FPoint& point) const;

	SDL_FPoint get_position() const { return m_position; }
 	void set_position(const SDL_FPoint& position);

	void set_limits(const SDL_Rect& limits) { m_limits = limits; }
	SDL_Rect get_limits() const { return m_limits; }

	void set_viewport_height(int height) { m_viewport_height = height; }
	int get_viewport_height() const { return m_viewport_height; }

	void set_viewport_width(int width) { m_viewport_width = width; }
	int get_viewport_width() const { return m_viewport_width; }

	void move(const SDL_FPoint& offset);
	void move(float x, float y);
};

