#include "stdafx.h"
#include "Drawing.h"
#include "DrawableObject.h"

void Drawing::init(float max_x, float max_y, int window_w, int window_h, SDL_Renderer * renderer)
{
	m_max_x = max_x;  m_max_y = max_y;
	m_window_w = window_w; m_window_h = window_h;
	m_renderer = renderer;
}

void Drawing::drawAxes()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	drawLine(Vector2(-m_max_x, 0.0), Vector2(m_max_x, 0.0f));
	drawLine(Vector2(0.0f, -m_max_y), Vector2(0.0f, m_max_y));

	// Add scale markings
	Vector2 origin = toScreenSpace(Vector2(0.0f, 0.0f)), screen_scale = toScreenSpace(Vector2(1.0f, 1.0f));
	screen_scale.x -= origin.x; screen_scale.y -= origin.y;
	float x = origin.x - screen_scale.x * m_max_x;
	while (x <= origin.x + screen_scale.x * m_max_x)
	{
		SDL_RenderDrawLineF(m_renderer, x, origin.y + 1.0f, x, origin.y - 1.0f);
		x += screen_scale.x;
	}
	float y = origin.y + screen_scale.y * m_max_y;
	while (y <= origin.y - screen_scale.y * m_max_y)
	{
		SDL_RenderDrawLineF(m_renderer, origin.x + 1.0f, y, origin.x - 1.0f, y);
		y -= screen_scale.y;
	}
}

void Drawing::drawObjects(const std::vector<DrawableObject*>& objects)
{
	for (auto object : objects)
	{
		SDL_SetRenderDrawColor(m_renderer, object->colour.r, object->colour.g, object->colour.b, 255);
		drawObject(object);
	}
}

// Draws a point in the correct place on the screen relative to the axes
void Drawing::drawPoint(const Vector2& p)
{
	Vector2 screen_pt = toScreenSpace(p);
	SDL_RenderDrawLineF(m_renderer, screen_pt.x - 2.5f, screen_pt.y - 2.5f, screen_pt.x + 2.5f, screen_pt.y + 2.5f);
	SDL_RenderDrawLineF(m_renderer, screen_pt.x - 2.5f, screen_pt.y + 2.5f, screen_pt.x + 2.5f, screen_pt.y - 2.5f);
}

// Draws a vector (a line with an optional arrow at the end)
// start: the position (x, y) relative to the origin to start drawing from
// end:  the position (x, y) relative to the origin to finish drawing
// withArrow: if true, an arrow will be drawn at the end of the vector to indicate direction
void Drawing::drawLine(const Vector2& start, const Vector2& end, bool withArrow)
{
	// Transform the points to screen space
	Vector2 start_screen = toScreenSpace(start), end_screen = toScreenSpace(end);

	// Draw the vector line
	SDL_RenderDrawLineF(m_renderer, start_screen.x, start_screen.y, end_screen.x, end_screen.y);

	if (withArrow)
	{
		// The vector between the points
		Vector2 v(end.x - start.x, end.y - start.y);

		// Draw the arrow at the end
		static const Vector2 arrow1(-0.2f, -0.2f), arrow2(-0.2f, 0.2f);
		float theta = atan2(v.y, v.x), cos_theta = cos(theta), sin_theta = sin(theta);
		Vector2 arrow1_rotated(arrow1.x * cos_theta - arrow1.y * sin_theta, arrow1.x * sin_theta + arrow1.y * cos_theta);
		Vector2 arrow2_rotated(arrow2.x * cos_theta - arrow2.y * sin_theta, arrow2.x * sin_theta + arrow2.y * cos_theta);

		Vector2 arrow1_screen = toScreenSpace(Vector2(arrow1_rotated.x + end.x, arrow1_rotated.y + end.y));
		Vector2 arrow2_screen = toScreenSpace(Vector2(arrow2_rotated.x + end.x, arrow2_rotated.y + end.y));
		SDL_RenderDrawLineF(m_renderer, end_screen.x, end_screen.y, arrow1_screen.x, arrow1_screen.y);
		SDL_RenderDrawLineF(m_renderer, end_screen.x, end_screen.y, arrow2_screen.x, arrow2_screen.y);
	}
}

// Draw a DrawableObject 
void Drawing::drawObject(const DrawableObject* object)
{
	std::vector<Vector2> points;
	object->getPoints(points);
	for (auto& p : points)
		drawPoint(p);

	std::vector<std::pair<Vector2, Vector2>> lines;
	object->getLines(lines);
	for (auto& l : lines)
		drawLine(l.first, l.second, object->drawArrows);
}

// Helper function to convert 'world' to screen (SDL) coordinates.
// Note that the world y-axis points upwards; the flip is handled here.
Vector2 Drawing::toScreenSpace(const Vector2& v)
{
	// Find the centre point of the drawn window
	static const float screen_origin_x = float(m_window_w / 2);
	static const float screen_origin_y = float(m_window_h / 2);

	// Map the scale of the x and y coordinates to the size of the window
	static const float scale_x = (float(m_window_w) - 20.0f) / (m_max_x * 2.0f);
	static const float scale_y = -(float(m_window_h) - 20.0f) / (m_max_y * 2.0f);

	return Vector2(v.x * scale_x + screen_origin_x, v.y * scale_y + screen_origin_y);
}