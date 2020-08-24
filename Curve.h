#pragma once
#include "DrawableObject.h"

// Unlike a Shape, a Curve is not described by a fixed set of points,
// but is generated from a formula that is used to evaluate the curve at
// specific intervals.
class Curve : public DrawableObject
{
public:
	Curve(float parameter_min, float parameter_max, float interval) :
		t_min(parameter_min), t_max(parameter_max), t_interval(interval) {}

	// Since we can't draw actual curves on the screen, we approximate them as a series of lines.
	virtual void getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const;

	// Define the range of the parameter and the interval at which to sample it.
	float t_min = 0.0f, t_max = 1.0f, t_interval = 0.1f;
};