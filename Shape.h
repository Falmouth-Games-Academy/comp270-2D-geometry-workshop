#pragma once
#include "DrawableObject.h"

// A Shape is a collection of points and lines to be drawn together.
// The points/lines can be stored in any format, but must be returned by the
// getPoints()/getLines() functions so that they can be drawn by the Application.
class Shape : public DrawableObject
{
public:
	// These functions apply the transform described by the given matrix to all points of the shape.
	virtual void applyMatrixTransformation(const Matrix22& m);
	virtual void applyMatrixTransformation(const Matrix22h& m);

protected:
	// This stores the current world-space points that define the shape.
	std::vector<Vector2> m_points;
};

// A point is a very simple shape...
class Point : public Shape
{
public:
	Point(Vector2 pos = Vector2(0.0f, 0.0f));
	void getPoints(std::vector<Vector2>& points) const;
};

// A line is also pretty simple.
class Line : public Shape
{
public:
	Line(Vector2 start = Vector2(0.0f, 0.0f), Vector2 end = Vector2(0.0f, 0.0f), bool isVector = false);
	void getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const;
};

// A simple stick-person
class StickDude : public Shape
{
public:
	// Constructor - takes the world-space position of the figure's centre as input
	StickDude(Vector2 centre = Vector2(0.0f, 0.0f));

	void getPoints(std::vector<Vector2>& points) const;
	void getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const;

private:
	// Define the positions of points that define the figure's outline, relative to its local centre.
	static const Vector2 neck;  
	static const Vector2 hips;
	static const Vector2 left_foot;
	static const Vector2 right_foot;
	static const Vector2 shoulder;
	static const Vector2 left_hand;
	static const Vector2 right_hand;
	static const Vector2 head1;
	static const Vector2 head2;
	static const Vector2 head3;
	static const Vector2 head4;
	static const Vector2 bowtie;
};

// A quadrilateral with a 'dot' (additional point drawn separately, to identify orientation)
class DotBox : public Shape
{
public:
	// Constructor - takes the four vertices a, b, c and d, and the position of the dot, t
	DotBox(Vector2 a = Vector2(0, 0), Vector2 b = Vector2(0, 0),
		Vector2 c = Vector2(0, 0), Vector2 d = Vector2(0, 0),
		Vector2 t = Vector2(0, 0));

	void getPoints(std::vector<Vector2>& points) const;
	void getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const;
};