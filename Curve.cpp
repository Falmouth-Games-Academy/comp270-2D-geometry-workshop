#include "stdafx.h"
#include "Curve.h"

void Curve::getLines(std::vector<std::pair<Vector2, Vector2>>& lines) const
{
	// Make sure there's no old data as we don't know where this vector has come from.
	lines.clear();

	// TO DO Add your implementation here to generate the set of lines that will describe your curve,
	// based on the parameter range and sampling interval (t_min, t_max and t_interval).
	// Each element of the returned vector 'lines' is a pair of Vector2 objects to define the start
	// and end points; you can add a new line using
	// lines.push_back( std::make_pair( Vector2(start_x, start_y), Vector2(end_x, end_y) ) );

}
