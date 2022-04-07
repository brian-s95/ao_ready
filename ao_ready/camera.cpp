#include "camera.h"

Camera::Camera()
:Camera(800, 800)
{
}

Camera::Camera(int viewport_width, int viewport_height)
:m_viewport_width(viewport_width)
,m_viewport_height(viewport_height)
,m_limits{}
,m_position{}
{
}

SDL_Rect Camera::get_viewport_rect() const
{
	SDL_Rect viewport;
	viewport.x = static_cast<int>(m_position.x);
	viewport.y = static_cast<int>(m_position.y);
	viewport.w = m_viewport_width;
	viewport.h = m_viewport_height;

	return viewport;
}

bool Camera::object_is_visible(const SDL_Rect& bounds)
{
	SDL_Rect viewport = get_viewport_rect();
	return SDL_HasIntersection(&viewport, &bounds);
}

bool Camera::object_is_visible(const SDL_FRect& bounds)
{
	SDL_Rect viewport = get_viewport_rect();
	SDL_Rect float_bounds =
	{
		static_cast<int>(bounds.x),
		static_cast<int>(bounds.y),
		static_cast<int>(bounds.w),
		static_cast<int>(bounds.h)
	};
	return SDL_HasIntersection(&viewport, &float_bounds);
}

SDL_Rect Camera::transform(const SDL_Rect& rect) const
{
	SDL_Rect dst;
	dst.x = rect.x - (int)m_position.x;
	dst.x = rect.x - (int)m_position.x;
	dst.w = rect.w;
	dst.h = rect.h;

	return dst;
}

SDL_FRect Camera::transform(const SDL_FRect& rect) const
{
	SDL_FRect dst;
	dst.x = rect.x - m_position.x;
	dst.x = rect.x - m_position.x;
	dst.w = rect.w;
	dst.h = rect.h;

	return dst;
}

SDL_Point Camera::transform(const SDL_Point& point) const
{
	int point_dst_x = point.x - m_position.x;
	int point_dst_y = point.y - m_position.y;

	return { point_dst_x, point_dst_y };
}

SDL_FPoint Camera::transform(const SDL_FPoint& point) const
{
	float point_dst_x = point.x - m_position.x;
	float point_dst_y = point.y - m_position.y;

	return { point_dst_x, point_dst_y };
}

void Camera::set_position(const SDL_FPoint& position)
{
	m_position = position;

	if (!SDL_RectEmpty(&m_limits))
	{
		m_position.x = SDL_clamp(m_position.x, m_limits.x, m_limits.w - m_viewport_width);
		m_position.y = SDL_clamp(m_position.y, m_limits.y, m_limits.h - m_viewport_height);
	}
}

void Camera::move(const SDL_FPoint& offset)
{
	move(offset.x, offset.y);
}

void Camera::move(float x, float y)
{
	float new_x = x - m_position.x;
	float new_y = y - m_position.y;

	set_position({ new_x, new_y });
}
