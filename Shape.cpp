#include "stdafx.h"
#include "Shape.h"

// Assigning values to static const class members
const Vector2 StickDude::neck(0.0f, 1.7f);
const Vector2 StickDude::hips(0.0f, 0.0f);
const Vector2 StickDude::left_foot(1.0f, -2.0f);
const Vector2 StickDude::right_foot(-1.0f, -2.0f);
const Vector2 StickDude::shoulder(0.0f, 1.25f);
const Vector2 StickDude::left_hand(0.5f, -0.1f);
const Vector2 StickDude::right_hand(-1.0f, 2.1f);
const Vector2 StickDude::head1(-0.25f, 1.7f);
const Vector2 StickDude::head2(0.25f, 1.7f);
const Vector2 StickDude::head3(0.25f, 2.2f);
const Vector2 StickDude::head4(-0.25f, 2.2f);
const Vector2 StickDude::bowtie(0.0f, 1.35f);

void Shape::applyMatrixTransformation(const Matrix22 & m)
{
	for (auto& point : m_points)
		point = m * point;
}

void Shape::applyMatrixTransformation(const Matrix22h & m)
{
	for (auto& point : m_points)
		point = (m * Vector2h(point)).asVector2();
}

Point::Point(Vector2 pos)
{
	m_points.resize(1);
	m_points[0] = pos;
}

void Point::getPoints(std::vector<Vector2>& points) const
{
	points.clear();
	points.push_back(m_points[0]);
}

Line::Line(Vector2 start, Vector2 end, bool isVector)
{
	m_points.resize(2);
	m_points[0] = start;
	m_points[1] = end;
	drawArrows = isVector;
}

void Line::getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const
{
	lines.clear();
	lines.push_back(std::make_pair(m_points[0], m_points[1]));
}

// StickDude constructor
StickDude::StickDude(Vector2 centre)
{
	m_points.resize(12);
	m_points[0] = centre + neck;
	m_points[1] = centre + hips;
	m_points[2] = centre + left_foot;
	m_points[3] = centre + right_foot;
	m_points[4] = centre + shoulder;
	m_points[5] = centre + left_hand;
	m_points[6] = centre + right_hand;
	m_points[7] = centre + head1;
	m_points[8] = centre + head2;
	m_points[9] = centre + head3;
	m_points[10] = centre + head4;
	m_points[11] = centre + bowtie;
}

void StickDude::getPoints(std::vector<Vector2>& points) const
{
	// Only the bowtie should be drawn separately; the other points are used to form lines.
	points.clear();
	points.push_back(m_points[11]);
}

void StickDude::getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const
{
	lines.clear();
	lines.push_back(std::make_pair(m_points[1], m_points[0]));	// from hips to neck
	lines.push_back(std::make_pair(m_points[1], m_points[2]));	// from hips to left foot
	lines.push_back(std::make_pair(m_points[1], m_points[3]));	// from hips to right foot
	lines.push_back(std::make_pair(m_points[4], m_points[5]));	// from shoulder to left hand
	lines.push_back(std::make_pair(m_points[4], m_points[6]));	// from shoulder to right hand
	lines.push_back(std::make_pair(m_points[7], m_points[8]));	// from head1 to head2
	lines.push_back(std::make_pair(m_points[8], m_points[9]));	// from head2 to head3
	lines.push_back(std::make_pair(m_points[9], m_points[10]));	// from head3 to head4
	lines.push_back(std::make_pair(m_points[10], m_points[7]));	// from head4 to head1
}

DotBox::DotBox(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2 t)
{
	m_points.resize(5);
	m_points[0] = a;
	m_points[1] = b;
	m_points[2] = c;
	m_points[3] = d;
	m_points[4] = t;
}

void DotBox::getPoints(std::vector<Vector2>& points) const
{
	// Only the 'dot' should be drawn separately; the other points define shapes's sides.
	points.clear();
	points.push_back(m_points[4]);
}

void DotBox::getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const
{
	lines.clear();
	lines.push_back(std::make_pair(m_points[0], m_points[1]));
	lines.push_back(std::make_pair(m_points[1], m_points[2]));
	lines.push_back(std::make_pair(m_points[2], m_points[3]));
	lines.push_back(std::make_pair(m_points[3], m_points[0]));
}
