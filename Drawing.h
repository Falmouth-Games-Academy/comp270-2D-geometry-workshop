#pragma once
#include "Vector2.h"

class DrawableObject;

// Utility class to help with drawing DrawableObjects to an SDL renderer.
class Drawing
{
public:
	void init(float max_x, float max_y, int window_w, int window_h, SDL_Renderer* renderer);

	void drawAxes();
	void drawObjects(const std::vector<DrawableObject*>& objects);

private:
	void drawPoint(const Vector2& p);
	void drawLine(const Vector2& start, const Vector2& end, bool withArrow = true);
	void drawObject(const DrawableObject* object);

	Vector2 toScreenSpace(const Vector2& v);

	// Store the axes ranges
	float m_max_x = 10.0f;
	float m_max_y = 10.0f;

	// Store the window dimensions
	int m_window_w = 100;
	int m_window_h = 100;

	// Keep a pointer to the renderer (NB not owned)
	SDL_Renderer* m_renderer = nullptr;
};