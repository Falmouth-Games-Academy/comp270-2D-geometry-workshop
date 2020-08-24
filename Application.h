#pragma once
#include "Scene.h"
#include "Drawing.h"

class Shape;

// Handles the main execution loop
class Application
{
public:
	Application();
	~Application();

	bool run();

private:
	bool initSDL();
	void shutdownSDL();

	void processEvent(const SDL_Event &e);
	void update();
	void render();

	const int c_windowWidth = 700;
	const int c_windowHeight = 700;
	const float c_max_x = 20;
	const float c_max_y = 20;

	SDL_Window *m_window = nullptr;
	SDL_Renderer *m_renderer = nullptr;

	Drawing m_draw;
	Scene m_scene;

	bool m_quit = false;
};
