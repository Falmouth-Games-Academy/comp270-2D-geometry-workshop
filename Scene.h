#pragma once
#include "Vector2.h"

class DrawableObject;

// A scene contains the objects to be drawn.
class Scene
{
public:
	~Scene();

	void setup(float max_x, float max_y);
	const std::vector<DrawableObject*>& getObjects() { return m_objects; }

private:
	// Functions for implementing week 2 workshop exercises
	void week2_exercise1();
	void week2_exercise2();
	void week2_exercise3();

	// Functions for implementing week 3 workshop exercises
	void week3_exercise1();
	void week3_exercise2();
	void week3_exercise3();
	void week3_exercise4();

	// Helper functions for adding various objects
	DrawableObject*	addPoint(float x, float y);
	DrawableObject*	addLine(float start_x, float start_y, float end_x, float end_y);
	DrawableObject*	addVector(Vector2 vec, float start_x = 0.0f, float start_y = 0.0f);
	DrawableObject*	addDude(float x, float y);
	DrawableObject*	addDotBox(float corner_x, float corner_y, float w, float h, float dot_x, float dot_y);
	DrawableObject* addCurve(float t_min, float t_max, float t_interval);

	// Generates a number of random vectors (with random colours).
	static void random_vectors(unsigned n, float min_x, float max_x, float min_y, float max_y,
						std::vector<std::pair<Vector2, Vector2>>& vectors,
						std::vector<int>& colours);

	// m_objects is an array of DrawableObjects (see DrawableObject.h)
	std::vector<DrawableObject*> m_objects;

	// The size of the grid
	float m_max_x = 0.0f, m_max_y = 0.0f;
};