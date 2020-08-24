#include "stdafx.h"
#include "Scene.h"
#include "Shape.h"
#include "Curve.h"
#include <random>

Scene::~Scene()
{
	for (auto object : m_objects)
		if (object) delete object;
}

//-------------------------------------------------------------------------------------//
// Edit the following functions to complete the exercises.

// Set up the scene by adding any objects you want to draw.
void Scene::setup(float max_x, float max_y)
{
	m_objects.clear();

	// Save the size of the working area
	m_max_x = max_x;
	m_max_y = max_y;

	// Week 2 exercises; you may wish to comment these out
	// as appropriate if your window becomes cluttered.
	week2_exercise1();
	week2_exercise2();
	week2_exercise3();

	// Week 3 exercises - uncomment these to start!
	//week3_exercise1();
	//week3_exercise2();
	//week3_exercise3();
	//week3_exercise4();
}

void Scene::week2_exercise1()
{
	Vector2 a(2.0f, 3.0f), b(1.0f, -2.0f);

	// Part a)
	DrawableObject* obj = addVector(a);
	obj->setColour(0, 0, 255);

	// Part b)
	obj = addVector(b);
	obj->setColour(0, 255, 0);

	// Part c)
	obj = addVector(2.0f * a);
	obj->setColour(255, 0, 0);

	// Part d)
	obj = addVector(-0.5f * b);
	obj->setColour(255, 0, 255);

	// Part e)
	obj = addVector(a + b);
	obj->setColour(127, 127, 255);

	// Part f)
	obj = addVector(a - b);
	obj->setColour(255, 255, 0);

	// Part g) - TO DO
	//obj = addVector(/* ... */);
	//obj->setColour(127, 127, 127);

	// Part h) - TO DO
	//obj = addVector(/* ... */);
	//obj->setColour(127, 127, 127);
}

void Scene::week2_exercise2()
{
	// Part d)
	float mag1 = Vector2(-12.0f, 5.0f).magnitude();

	// Part e) - TO DO
	//float mag2 = /* ... */;

	// Part f) - TO DO
	//float mag3 = /* ... */;
}

void Scene::week2_exercise3()
{
	DrawableObject* curve = addCurve(0.0f, 2.0f * M_PI, M_PI / 5.0f);
	curve->setColour(255, 0, 0);
}

void Scene::week3_exercise1()
{
	// Generate a number of vectors
	const int num_vecs = 20;
	std::vector<std::pair<Vector2, Vector2>> vectors;
	std::vector<int> colours;
	random_vectors(num_vecs, -m_max_x, m_max_x, -m_max_y, m_max_y, vectors, colours);

	unsigned ci = 0;	// index in the colours array
	DrawableObject* obj = nullptr;
	for (auto vec_pair : vectors)
	{
		// The vectors array contains pairs, with the vector
		// itself as the first element and its start point the second
		Vector2 vec = vec_pair.first;
		Vector2 start = vec_pair.second;

		// Create the drawable object
		// TO DO: first check that it's pointing in the right direction...
		obj = addVector(vec, start.x, start.y);

		// Assign the colour from the array
		obj->setColour(colours[ci++], colours[ci++], colours[ci++]);
	}
}

void Scene::week3_exercise2()
{
	// Generate two vectors
	const int num_vecs = 2;
	std::vector<std::pair<Vector2, Vector2>> vectors;
	std::vector<int> colours;
	random_vectors(num_vecs, 0.0f, m_max_x, 0.0f, m_max_y, vectors, colours);

	// Extract the vectors from the result and add to the scene;
	// NB we don't care about the start points for this exercise,
	// so just draw them at the origin.
	Vector2 v1 = vectors[0].first;
	Vector2 v2 = vectors[1].first;

	DrawableObject* obj = addVector(v1);
	obj->setColour(colours[0], colours[1], colours[2]);

	obj = addVector(v2);
	obj->setColour(colours[3], colours[4], colours[5]);

	// TO DO: compute the projection of v1 onto v2
	Vector2 v1_proj;

	// Draw the projection
	//obj = addVector(v1_proj);
	//obj->setColour(255, 0, 0);
}

void Scene::week3_exercise3()
{
	// Some example objects to apply matrix transforms to.
	DrawableObject* obj = addPoint(-7.0f, 5.0f);
	obj->setColour(255, 0, 0);
	
	obj = addDude(3.0f, 2.0f);
	obj->setColour(255, 0, 255);

	// Create a second dude to apply a matrix to
	obj = addDude(3.0f, 2.0f);
	obj->setColour(255, 255, 0);
	
	// Apply the matrix from question 4a of part A
	Matrix22 a(0, 1, -1, 0);
	obj->applyMatrixTransformation(a);

	// Another dude...
	obj = addDude(3.0f, 2.0f);
	obj->setColour(0, 255, 0);

	// Apply a product of the matrices from 4a and 4e;
	// what happens if you change the multiplication order?
	Matrix22 e(-1, 0, 0, 1);
	obj->applyMatrixTransformation(e * a);
}

void Scene::week3_exercise4()
{
	// The box-with-a-dot from question 7 of part A;
	// create two to see the effect of the transform.
	DrawableObject* obj = addDotBox(-1.0f, 0.0f, 2.0f, 3.0f, 0.5f, 2.5f);
	obj->setColour(63, 63, 255);

	obj = addDotBox(-1.0f, 0.0f, 2.0f, 3.0f, 0.5f, 2.5f);
	obj->setColour(128, 128, 255);

	// Apply a translation matrix to the box
	Matrix22h tm;
	tm.setTranslate(0.0f, 0.0f);	// TO DO enter the correct translation values.
	obj->applyMatrixTransformation(tm);

	// TODO Combine the translation matrix with another
	// transform to get the required result. The easiest way
	// to create a non-translation Matrix22h is to first create
	// it as a Matrix22 and then convert it, e.g.
	// Matrix22 m(/*...*/);
	// Matrix22h mh(m);
}

//-------------------------------------------------------------------------------------//

DrawableObject* Scene::addPoint(float x, float y)
{
	Point* p = new Point(Vector2(x, y));
	m_objects.push_back(p);
	return p;
}

DrawableObject* Scene::addLine(float start_x, float start_y, float end_x, float end_y)
{
	Line* line= new Line(Vector2(start_x, start_y), Vector2(end_x, end_y));
	m_objects.push_back(line);
	return line;
}

DrawableObject* Scene::addVector(Vector2 vec, float start_x, float start_y)
{
	Vector2 start_vec(start_x, start_y);
	Line* vecLine = new Line(start_vec, start_vec + vec);
	vecLine->drawArrows = true;
	m_objects.push_back(vecLine);
	return vecLine;
}

DrawableObject* Scene::addDude(float x, float y)
{
	StickDude* dude = new StickDude(Vector2(x, y));
	m_objects.push_back(dude);
	return dude;
}

DrawableObject* Scene::addDotBox(float corner_x, float corner_y, float w, float h, float dot_x, float dot_y)
{
	Vector2 a(corner_x, corner_y), b(corner_x, corner_y + h),
		c(corner_x + w, corner_y + h), d(corner_x + w, corner_y), t(dot_x, dot_y);
	
	DotBox* box = new DotBox(a, b, c, d, t);
	m_objects.push_back(box);
	return box;
}

DrawableObject * Scene::addCurve(float t_min, float t_max, float t_interval)
{
	Curve* curve = new Curve(t_min, t_max, t_interval);
	m_objects.push_back(curve);
	return curve;
}

// Generates a given number, n, of random vectors in the specified working area.
// The 'vectors' array is populated with pairs of (vector, vector start);
// the colours array contains three integer values in the range [0, 255] for each vector.
void Scene::random_vectors(unsigned n, float min_x, float max_x, float min_y, float max_y,
							std::vector<std::pair<Vector2, Vector2>>& vectors, std::vector<int>& colours)
{
	// Initialise the return arrays
	vectors.clear();
	colours.clear();
	vectors.resize(n);
	colours.resize(n * 3);
	
	// Set up the random number generator; see
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<> x_distribution(min_x, max_x);
	std::uniform_real_distribution<> y_distribution(min_y, max_y);
	std::uniform_int_distribution<> colour_distribution(0, 255);

	Vector2 start, end;
	unsigned ci = 0;	// index in the colours array
	for (unsigned i = 0; i < n; ++i)
	{
		// Generate random start and end points
		start.x = static_cast<float>(x_distribution(generator));
		start.y = static_cast<float>(y_distribution(generator));
		end.x = static_cast<float>(x_distribution(generator));
		end.y = static_cast<float>(y_distribution(generator));

		// Add the vector between the points and its start to the array
		vectors[i].first = end - start;
		vectors[i].second = start;

		// Assign a random colour
		colours[ci++] = colour_distribution(generator);
		colours[ci++] = colour_distribution(generator);
		colours[ci++] = colour_distribution(generator);
	}
}
