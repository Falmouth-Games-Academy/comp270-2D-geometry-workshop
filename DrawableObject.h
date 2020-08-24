#pragma once
#include "Vector2h.h"

// An object that provides a set of points and lines to draw.
class DrawableObject
{
public:
	// This function should be implemented by derived classes to populate 'points'
	// with all the x,y values to draw as individual points (formatted as Vector2 values
	// for convenience only)
	virtual void getPoints(std::vector<Vector2>& points) const { points.clear(); }

	// This function should be implemented by derived classes to populate 'lines'
	// with pairs of vectors representing points to lines between. The first
	// item in each pair should be the start point, and the second is the end.
	virtual void getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const { lines.clear(); }

	// Each shape can be assigned a colour; the default is white.
	struct { int r = 255; int g = 255; int b = 255; } colour;
	void setColour(int r, int g, int b) { colour.r = r; colour.g = g; colour.b = b; }

	// Indicates whether to draw arrows on the lines (i.e. they are vectors)
	bool drawArrows = false;

	// Technically, we could transform any drawable object, but it doesn't necessarily
	// make sense for all of them, so provide a default implementation that does nothing.
	virtual void applyMatrixTransformation(const Matrix22& m) {}
	virtual void applyMatrixTransformation(const Matrix22h& m) {}
};